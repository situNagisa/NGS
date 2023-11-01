#pragma once

#include "./multiply/numeric.h"
#include "./multiply/vector.h"
#include "./multiply/matrix.h"

NGS_MATH_MATRIX_BEGIN

template<class _L, class _R>
	requires functor::multipliable_with_number<_L, _R>
constexpr decltype(auto) multiply(_L&& left, _R&& right)
{
	return detail_arithmetic::multiply_number(NGS_PP_PERFECT_FORWARD(left), NGS_PP_PERFECT_FORWARD(right));
}

template<class _L, class _R>
	requires functor::multipliable_with_vector<_L, _R>
constexpr decltype(auto) multiply(_L&& left, _R&& right)
{
	return detail_arithmetic::multiply_vector(NGS_PP_PERFECT_FORWARD(left), NGS_PP_PERFECT_FORWARD(right));
}

template<class _L, class _R>
	requires functor::multipliable_with_matrix<_L, _R>
constexpr decltype(auto) multiply(_L&& left, _R&& right)
{
	return detail_arithmetic::multiply_matrix(NGS_PP_PERFECT_FORWARD(left), NGS_PP_PERFECT_FORWARD(right));
}

template<class _L, class _R>
	requires requires(_L left, _R right) { matrixes::multiply(NGS_PP_PERFECT_FORWARD(left), NGS_PP_PERFECT_FORWARD(right)); }
constexpr decltype(auto) operator*(_L&& left, _R&& right)
{
	return matrixes::multiply(NGS_PP_PERFECT_FORWARD(left), NGS_PP_PERFECT_FORWARD(right));
}


NGS_MATH_MATRIX_END