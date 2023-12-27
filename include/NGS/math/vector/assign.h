#pragma once

#include "./concept.h"
#include "./size.h"

NGS_LIB_BEGIN

namespace NGS_MATH_VECTOR_CPT_NS
{
	template<class _L, class _R>
	concept assignable_from = input_vector<_R> && output_vector<_L, ::std::ranges::range_value_t<_R> >&& maybe_same_extent<_L, _R>;
}


template<class _L, class _R> requires assignable_from<_L, _R>
constexpr void assign(_L&& output, _R&& input)
{
	NGS_MATH_VECTOR_CHECK_SIZE(output, input);
	::std::ranges::copy(NGS_PP_PERFECT_FORWARD(input), ::std::ranges::begin(NGS_PP_PERFECT_FORWARD(output)));
}

NGS_LIB_END