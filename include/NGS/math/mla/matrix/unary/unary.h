#pragma once

#include "NGS/math/mla/matrix/expression/expression.h"
#include "NGS/math/mla/matrix/expression/container.h"
#include "NGS/math/mla/matrix/unary/functor.h"
#include "NGS/math/mla/matrix/traits.h"

NGS_MLA_BEGIN

template<CMatrixExpression _Expression, CMatrixUnaryFunctor<_Expression> _Functor, ccpt::UInt _Row, ccpt::UInt _Col>
class NGS_API  MatrixUnary : public MatrixExpression<MatrixUnary<_Expression, _Functor, _Row, _Col>> {
	NGS_menvironment(MatrixUnary);
public:
	using expression_type = typename base_type::expression_type;
private:
	using functor_type = _Functor;
	using original_expression_type = typename matrix_traits<_Expression>::original_type;
	using expression_closure_type = typename matrix_traits<_Expression>::closure_type;
public:
	using element_type = typename matrix_traits<_Expression>::element_type;
	constexpr static size_t complexity = matrix_traits<_Expression>::complexity + 1;

	constexpr static size_t row_count = _Row::value;
	constexpr static size_t col_count = _Col::value;
	constexpr static size_t element_count = row_count * col_count;

	constexpr explicit MatrixUnary(expression_closure_type expression) noexcept
		: _expression(expression)
	{}

	using base_type::operator();
	constexpr element_type operator()(size_t row_index, size_t col_index)const { return functor_type::apply(_expression, row_index, col_index); }
private:
	expression_closure_type _expression;
};
//verify

template<CMatrixExpression _Expression, CMatrixUnaryFunctor<_Expression> _Functor, size_t _Row = matrix_traits<_Expression>::row_count, size_t _Col = matrix_traits<_Expression>::col_count>
using matrix_unary_functor_t = MatrixUnary<
	_Expression, _Functor,
	std::integral_constant<size_t, _Row>, std::integral_constant<size_t, _Col>
>;

template<CMatrixExpression _Expression, template<class >class  _Functor, size_t _Row = matrix_traits<_Expression>::row_count, size_t _Col = matrix_traits<_Expression>::col_count>
using matrix_unary_scalar_functor_t = matrix_unary_functor_t<
	_Expression,
	MatrixUnaryScalarFunctor<_Expression, _Functor<typename matrix_traits<_Expression>::element_type>>,
	_Row, _Col
>;

NGS_MLA_END
