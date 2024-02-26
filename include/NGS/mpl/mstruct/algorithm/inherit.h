#pragma once

#include "../basic.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

namespace _detail
{
	template<class, class> struct inherit_functor {};

	template<class T, class Base> requires requires { typename type_traits::object_t<T>::template inherit<Base>; }
	struct inherit_functor<T, Base>
	{
		using type = typename type_traits::object_t<T>::template inherit<Base>::type;
	};

	template<class T, class Base = T>
	concept inheritable = basic::structure<typename inherit_functor<T, Base>::type>;

	template<class, class...> struct multi_inherit_functor {};

	template<class T, class... Bases> requires requires { typename type_traits::object_t<T>::template inherit<Bases...>; }
	struct multi_inherit_functor<T, Bases...>
	{
		using type = typename type_traits::object_t<T>::template inherit<Bases...>::type;
	};

	template<class T, class... Bases>
	concept multi_inheritable = basic::structure<typename multi_inherit_functor<T, Bases...>::type>;
}

template<class T, class Base = T, class... Bases>
concept inheritable = (!sizeof...(Bases) && _detail::inheritable<T, Base>) || _detail::multi_inheritable<T, Base, Bases...>;

template<class T, class Base, class... Bases>
struct inherit
{
	using type = type_traits::naked_t<decltype([]
		{
			if constexpr (!sizeof...(Bases))
			{
				return declval<_detail::inherit_functor<T, Base>>();
			}
			else
			{
				return declval<_detail::multi_inherit_functor<T, Base, Bases...>>();
			}
		}()) > ;
};

template<class T, class Base, class... Bases>
using inherit_t = typename inherit<T, Base, Bases...>::type;

NGS_LIB_MODULE_END