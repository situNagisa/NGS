#pragma once

#include "./transform.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

template<class _T>
using trivial_view = transform_default_sentinel_view <
	[](index_t, index_t, auto&& value) {return value; },
	adapter_extent, adapter_extent,
	_T > ;

constexpr auto trivial(auto&& value)
{
	return trivial_view<type_traits::naked_t<decltype(value)>>(NGS_PP_PERFECT_FORWARD(value));
}

namespace _detail
{
	using zero_matrix = NGS_MATH_MATRIX_TAG_NS::retag<NGS_MATH_MATRIX_TAG_NS::zero, trivial_view<bool>>;
}

inline constexpr _detail::zero_matrix zero{ false };

NGS_LIB_MODULE_END