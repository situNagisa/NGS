#pragma once

#include "../get.h"
#include "./tuple.h"
#include "./size.h"
#include "./element.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN
namespace _detail
{
	template<size_t _Index>
	constexpr decltype(auto) get_recurse(auto&& p)
	{
		constexpr auto index = _Index;
		using tuple_type = decltype(p);
		NGS_ASSERT_IF_CONSTEXPR(index < size_v<tuple_type>, "index out of range")
		{
			if constexpr (index == size_v<tuple_type> -1)
			{
				return NGS_PP_PERFECT_FORWARD(p).value();
			}
			else
			{
				return _detail::get_recurse<index>(NGS_PP_PERFECT_FORWARD(p).base());
			}
		}
	}

	template<size_t _Index>
	constexpr decltype(auto) get_value(auto&& p)
	{
		using tuple_type = decltype(p);

		using element_type = element_t<_Index, tuple_type>;
		using return_type = ::std::conditional_t<::std::is_const_v<type_traits::object_t<tuple_type>>, const element_type&, element_type&>;

		return static_cast<return_type>(_detail::get_recurse<size_v<tuple_type> -_Index - 1>(NGS_PP_PERFECT_FORWARD(p)));
	}
}

template<size_t _Index, class... _Args>
constexpr decltype(auto) get(tuple<_Args...>& t) { return _detail::get_value<_Index>(NGS_PP_PERFECT_FORWARD(t)); }
template<size_t _Index, class... _Args>
constexpr decltype(auto) get(const tuple<_Args...>& t) { return _detail::get_value<_Index>(NGS_PP_PERFECT_FORWARD(t)); }
template<size_t _Index, class... _Args>
constexpr decltype(auto) get(tuple<_Args...>&& t) { return _detail::get_value<_Index>(NGS_PP_PERFECT_FORWARD(t)); }
template<size_t _Index, class... _Args>
constexpr decltype(auto) get(const tuple<_Args...>&& t) { return _detail::get_value<_Index>(NGS_PP_PERFECT_FORWARD(t)); }

NGS_LIB_MODULE_END
