#pragma once

#include "./defined.h"

NGS_STL_TUPLE_BEGIN

#if defined(NGS_CPP_STANDARD_HAS_23) && defined(__cpp_lib_tuple_like)
using std::tuple_like;
#else

template<class _T>
constexpr bool _tuple_like_impl()
{
	if constexpr (!requires{ { std::tuple_size_v<_T> } -> std::convertible_to<std::size_t>; })
	{
		return false;
	}
	if constexpr (!std::tuple_size_v<_T>)
	{
		return true;
	}
	else if constexpr (!requires(_T & __t) { { std::get<0>(__t) } -> std::convertible_to<std::tuple_element_t<0, _T>&>; })
	{
		return false;
	}
	else if constexpr (!requires(_T & __t) { { std::get<0>(std::move(__t)) } -> std::convertible_to<std::tuple_element_t<0, _T>&&>; })
	{
		return false;
	}
	else
	{
		return true;
	}
}

template<class _T>
concept tuple_like = _tuple_like_impl<_T>();
#endif

NGS_STL_TUPLE_END