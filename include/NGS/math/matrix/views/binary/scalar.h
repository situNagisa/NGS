#pragma once

#include "./defined.h"

NGS_LIB_MODULE_BEGIN

namespace _detail
{
	template<class _L, class _R>
	concept multiply_scalar_operatable = (operator_matrix<_L> && scalar<_R>) || (scalar<_L> && operator_matrix<_R>);
}


using vectors::views::add_scalar_view;
using vectors::views::subtract_scalar_view;
using vectors::views::multiply_scalar_view;
using vectors::views::divide_scalar_view;

using vectors::views::add_scalar;
using vectors::views::subtract_scalar;
using vectors::views::multiply_scalar;
using vectors::views::divide_scalar;

NGS_LIB_MODULE_END
NGS_MATH_MATRIX_OPERATOR_BEGIN

template<class _L, class _R> requires NGS_LIB_MODULE_NAME::_detail::multiply_scalar_operatable<_L, _R>
constexpr decltype(auto) operator+(_L&& left, _R&& right)
{
	return NGS_LIB_MODULE_NAME::add_scalar(NGS_PP_PERFECT_FORWARD(left), NGS_PP_PERFECT_FORWARD(right));
}

template<class _L, class _R> requires NGS_LIB_MODULE_NAME::_detail::multiply_scalar_operatable<_L, _R>
constexpr decltype(auto) operator-(_L&& left, _R&& right)
{
	return NGS_LIB_MODULE_NAME::subtract_scalar(NGS_PP_PERFECT_FORWARD(left), NGS_PP_PERFECT_FORWARD(right));
}

template<class _L, class _R> requires NGS_LIB_MODULE_NAME::_detail::multiply_scalar_operatable<_L, _R>
constexpr decltype(auto) operator*(_L&& left, _R&& right)
{
	return NGS_LIB_MODULE_NAME::multiply_scalar(NGS_PP_PERFECT_FORWARD(left), NGS_PP_PERFECT_FORWARD(right));
}

template<class _L, class _R> requires NGS_LIB_MODULE_NAME::_detail::multiply_scalar_operatable<_L, _R>
constexpr decltype(auto) operator/(_L&& left, _R&& right)
{
	return NGS_LIB_MODULE_NAME::divide_scalar(NGS_PP_PERFECT_FORWARD(left), NGS_PP_PERFECT_FORWARD(right));
}

NGS_MATH_MATRIX_OPERATOR_END