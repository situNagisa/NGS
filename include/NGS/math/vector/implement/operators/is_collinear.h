#pragma once

#include "NGS/math/vector/concept.h"
#include "./product.h"
#include "./norm.h"

NGS_MATH_VECTOR_BEGIN

constexpr bool is_collinear(auto&& left, auto&& right) noexcept
	requires requires
{
	(product_inner(NGS_PERFECT_FORWARD(left), NGS_PERFECT_FORWARD(right)) * product_inner(NGS_PERFECT_FORWARD(left), NGS_PERFECT_FORWARD(right))) == 
		(norm_squared(NGS_PERFECT_FORWARD(left)) * norm_squared(NGS_PERFECT_FORWARD(right)));
}
{
	auto inner = product_inner(NGS_PERFECT_FORWARD(left), NGS_PERFECT_FORWARD(right));
	return inner * inner == (norm_squared(NGS_PERFECT_FORWARD(left)) * norm_squared(NGS_PERFECT_FORWARD(right)));
}

NGS_MATH_VECTOR_END