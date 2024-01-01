#pragma once

#include "../get.h"
#include "../element.h"
#include "../size.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN
namespace _detail
{
	template<class _T>
	concept tuple_like = requires{ requires !size_v<_T>; } || requires(_T t)
	{
		{ get<size_v<_T> -1>(t) } -> cpt::naked_same_as<element_t<size_v<_T> -1, _T>>;
	};
}

template<class _T>
concept tuple_like = _detail::tuple_like<type_traits::object_t<_T>>;
NGS_LIB_MODULE_END