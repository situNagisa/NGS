#pragma once

#include "NGS/math/vector/concept.h"

NGS_MATH_VECTOR_BEGIN

template<functor::expression _L, functor::expression _R>
	requires functor::dimension_equality<_L, _R>&& std::equality_comparable_with<functor::value_t<_L>, functor::value_t<_R>>
constexpr bool equality(_L&& left, _R&& right)
{
	for (size_t i = 0; i < functor::dimension<_L>; i++)
	{
		if (functor::access(NGS_PERFECT_FORWARD(left), i) != functor::access(NGS_PERFECT_FORWARD(right), i))
			return false;
	}
	return true;
}

constexpr decltype(auto) operator==(auto&& left, auto&& right)
	requires requires{ vectors::equality(NGS_PERFECT_FORWARD(left), NGS_PERFECT_FORWARD(right)); }
{
	return vectors::equality(NGS_PERFECT_FORWARD(left), NGS_PERFECT_FORWARD(right));
}

NGS_MATH_VECTOR_END