#pragma once

#include "../extent.h"
#include "../operate.h"
#include "../param_trait.h"
#include "../iterator.h"
#include "./transform.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

template<input_vector _V>
using normalize_view = transform_view < extent_v<_V>, [](index_t index, input_vector auto&& vector, auto norm)
	{
		return NGS_MATH_VECTOR_OPERATE_NS::access(NGS_PP_PERFECT_FORWARD(vector), index) / norm;
	},
	[](input_vector auto&& vector, auto)
	{
		return ::std::ranges::size(vector);
	}, _V&&, NGS_MATH_VECTOR_OPERATE_NS::norm_t<_V >> ;

constexpr auto normalize(input_vector auto&& vector)
{
	return normalize_view<decltype(vector)>(NGS_PP_PERFECT_FORWARD(vector), NGS_MATH_VECTOR_OPERATE_NS::norm(vector));
}

NGS_LIB_MODULE_END