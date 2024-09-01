#pragma once

#include "../get.h"
#include "../element.h"
#include "../size.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN
namespace _detail
{
	template<class T>
	concept tuple_like = requires{ requires !size<T>::value; } || requires(T t)
	{
		{ get<size<T>::value - 1>(t) } -> ::std::same_as<element_t<size<T>::value - 1, T>>;
	};
}

template<class T>
concept tuple_like = _detail::tuple_like<type_traits::object_t<T>>;
NGS_LIB_MODULE_END