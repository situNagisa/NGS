#pragma once

#include "../../access.h"
#include "../../../standard/binary.h"

NGS_MATH_MATRIX_FUNCTOR_BEGIN

template<class _L, class _R>
concept multipliable_with_matrix = requires(_L left, _R right, size_t row_index, size_t col_index)
{
	requires expression<_L>;
	requires expression<_R>;
	{ row(NGS_PERFECT_FORWARD(left), row_index) } -> vectors::functor::expression;
	{ column(NGS_PERFECT_FORWARD(right), col_index) } -> vectors::functor::expression;
	requires vectors::functor::inner_productable<decltype(row(NGS_PERFECT_FORWARD(left), row_index)), decltype(column(NGS_PERFECT_FORWARD(right), col_index))>;
};

NGS_MATH_MATRIX_FUNCTOR_END

NGS_MATH_MATRIX_BEGIN  namespace detail_arithmetic {

inline constexpr struct {
	constexpr decltype(auto) operator()(auto&& left, auto&& right, size_t row_index, size_t column_index)
	{
		return vectors::product_inner(row(NGS_PERFECT_FORWARD(left), row_index), column(NGS_PERFECT_FORWARD(right), column_index));
	}
}multiply_access{};

inline constexpr struct
{
	constexpr decltype(auto) operator()(functor::expression auto&& left, functor::expression auto&& right) const
		requires functor::multipliable_with_matrix<decltype(left), decltype(right)>
	{
		return functor::binary_functor<decltype(left), decltype(right), functor::rows<decltype(left)>, functor::columns<decltype(left)>, multiply_access>{NGS_PERFECT_FORWARD(left), NGS_PERFECT_FORWARD(right)};
	}
}multiply_matrix;

}

using detail_arithmetic::multiply_matrix;


NGS_MATH_MATRIX_END