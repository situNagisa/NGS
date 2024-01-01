#pragma once

#include "../extent.h"
#include "./transform.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

template<input_vector _V>
using negate_view = transform_depend_view < _V, [](index_t index, input_vector auto&& vector)
	{
		return -NGS_MATH_VECTOR_OPERATE_NS::access(NGS_PP_PERFECT_FORWARD(vector), index);
	} > ;

constexpr auto negate(input_vector auto&& vector)
{
	return negate_view<decltype(vector)>(NGS_PP_PERFECT_FORWARD(vector));
}

NGS_LIB_MODULE_END
NGS_LIB_BEGIN

constexpr auto operator-(input_vector auto&& vector) requires tag_vector<decltype(vector)>&& scalar_vector<decltype(vector)>
{
	return NGS_LIB_MODULE_NAME::negate(NGS_PP_PERFECT_FORWARD(vector));
}

NGS_LIB_END