#pragma once

#include "../extent.h"
#include "../operate.h"
#include "./transform.h"

#include "./defined.h"

NGS_LIB_MODULE_BEGIN

template<input_vector _V>
using normalize_view = transform_view < [](index_t index, input_vector auto&& vector, auto norm)
	{
		return NGS_MATH_VECTOR_OPERATE_NS::access(NGS_PP_PERFECT_FORWARD(vector), index) / norm;
	},
	extent_v<_V>,
	packet< _V&&, NGS_MATH_VECTOR_OPERATE_NS::norm_t<_V >>,
	[](input_vector auto&& vector, auto)
	{
		return ::std::ranges::size(vector);
	} > ;


constexpr auto normalize(input_vector auto&& vector)
{
	return normalize_view<decltype(vector)>(NGS_PP_PERFECT_FORWARD(vector), NGS_MATH_VECTOR_OPERATE_NS::norm(vector));
}

NGS_LIB_MODULE_END