#pragma once

#include "./defined.h"

NGS_LIB_BEGIN

#if defined(NGS_CPP_STANDARD_HAS_23) && defined(__cpp_lib_tuple_like)
using std::tuple_like;
#else
namespace detail
{
	template<class _T> constexpr bool is_array_impl = false;
	template<class _T, size_t _Size> constexpr bool is_array_impl<std::array<_T, _Size>> = true;

	template<class _T> constexpr bool is_subrange_impl = false;
	template<class _Iterator, class _Sequence, std::ranges::subrange_kind _Kind> constexpr bool is_subrange_impl<std::ranges::subrange<_Iterator, _Sequence, _Kind>> = true;

	template<class _T>
	constexpr bool tuple_like_impl()
	{
		using object_type = type_traits::object_t<_T>;
		return cpt::is_specialization_of<object_type, std::tuple> || cpt::is_specialization_of<object_type, std::pair> || is_array_impl<object_type> || is_subrange_impl<object_type>;
	}

}

template<class _T>
concept tuple_like = detail::tuple_like_impl<_T>();
#endif


NGS_LIB_END