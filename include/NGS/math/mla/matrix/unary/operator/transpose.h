#pragma once

#include "NGS/math/mla/scalar/unary.h"
#include "NGS/math/mla/matrix/unary/unary.h"

NGS_MLA_BEGIN

template<CMatrixExpression _Expression>
struct MatrixUnaryTransposeFunctor {
private:
	using expression_type = _Expression;
	using result_type = typename matrix_traits<expression_type>::element_type;
public:

	constexpr static result_type apply(const expression_type& expr, size_t row_index, size_t col_index) {
		return expr()(col_index, row_index);
	}
};

template<CMatrixExpression _Expression>
constexpr matrix_unary_functor_t<
	_Expression,
	MatrixUnaryTransposeFunctor<_Expression>,
	matrix_traits<_Expression>::col_count, matrix_traits<_Expression>::row_count
> transpose(const _Expression& expression) {
	return matrix_unary_functor_t<
		_Expression,
		MatrixUnaryTransposeFunctor<_Expression>,
		matrix_traits<_Expression>::col_count, matrix_traits<_Expression>::row_count
	>(expression);
}

NGS_MLA_END
