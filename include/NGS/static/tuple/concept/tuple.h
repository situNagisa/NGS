#pragma once

#include "../get.h"
#include "../element.h"
#include "../size.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN
namespace _detail
{
	template<class _T>
	concept tuple_like = requires{ requires !size<_T>::value; } || requires(_T t)
	{
		{ get<size<_T>::value - 1>(t) } -> cpt::naked_same_as<element_t<size<_T>::value - 1, _T>>;
	};
}

template<class _T>
concept tuple_like = _detail::tuple_like<type_traits::object_t<_T>>;
NGS_LIB_MODULE_END