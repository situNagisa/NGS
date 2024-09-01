#pragma once

#include "../extent.h"
#include "./transform.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

template<accessable_vector _V>
using negate_view = transform_depend_view < [](index_t index, accessable_vector auto&& vector)
	{
		return -NGS_MATH_VECTOR_OPERATE_NS::access(NGS_PP_PERFECT_FORWARD(vector), index);
	}, _V > ;


constexpr auto negate(accessable_vector auto&& vector)
{
	return negate_view<decltype(vector)>(NGS_PP_PERFECT_FORWARD(vector));
}

NGS_LIB_MODULE_END
NGS_MATH_VECTOR_OPERATOR_BEGIN

constexpr auto operator-(accessable_vector auto&& vector) requires operator_vector<decltype(vector)>
{
	return NGS_LIB_MODULE_NAME::negate(NGS_PP_PERFECT_FORWARD(vector));
}

NGS_MATH_VECTOR_OPERATOR_END