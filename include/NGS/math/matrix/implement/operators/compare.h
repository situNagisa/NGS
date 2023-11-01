#pragma once

#include "NGS/math/matrix/concept.h"

NGS_MATH_MATRIX_BEGIN

template<functor::expression _L, functor::expression _R>
	requires functor::same_type<_L, _R>&& std::equality_comparable_with<functor::value_t<_L>, functor::value_t<_R>>
constexpr bool equality(_L&& left, _R&& right)
{
	for (size_t r = 0; r < functor::rows<_L>; r++)
	{
		for (size_t c = 0; c < functor::columns<_L>; c++)
		{
			if (functor::access(NGS_PP_PERFECT_FORWARD(left), r, c) != functor::access(NGS_PP_PERFECT_FORWARD(right), r, c))
				return false;
		}
	}
	return true;
}

constexpr decltype(auto) operator==(auto&& left, auto&& right)
	requires requires{ vectors::equality(NGS_PP_PERFECT_FORWARD(left), NGS_PP_PERFECT_FORWARD(right)); }
{
	return vectors::equality(NGS_PP_PERFECT_FORWARD(left), NGS_PP_PERFECT_FORWARD(right));
}

NGS_MATH_MATRIX_END