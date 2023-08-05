#pragma once

#include "NGS/mla/matrix/expression/concept.h"
#include "NGS/mla/vector/expression.h"
#include "NGS/mla/matrix/traits.h"

NGS_MLA_BEGIN

template<CMatrixExpression _Expressioin>
struct MatrixRowVector : VectorExpression<MatrixRowVector<_Expressioin>> {
private:
	using base_type = MatrixRowVector::self_type;
protected:
	using self_type = MatrixRowVector<_Expressioin>;
public:
	using element_type = typename matrix_traits<_Expressioin>::element_type;
	constexpr static size_t dimension = matrix_traits<_Expressioin>::col_count;
	constexpr static size_t complexity = matrix_traits<_Expressioin>::complexity + 1;
private:
	using _expression_closure_type = typename matrix_traits<_Expressioin>::closure_type;
public:
	constexpr MatrixRowVector(_expression_closure_type expression, size_t row) : _expression(expression), _row(row) {}

	using base_type::operator();
	constexpr element_type operator()(size_t index)const { return _expression()(_row, index); }

private:
	_expression_closure_type _expression;
	size_t _row = 0;
};
//verify

template<CMatrixExpression _Expressioin>
struct MatrixColVector : VectorExpression<MatrixColVector<_Expressioin>> {
private:
	using base_type = MatrixColVector::self_type;
protected:
	using self_type = MatrixColVector<_Expressioin>;
public:
	using element_type = typename matrix_traits<_Expressioin>::element_type;
	constexpr static size_t dimension = matrix_traits<_Expressioin>::row_count;
	constexpr static size_t complexity = matrix_traits<_Expressioin>::complexity + 1;
private:
	using _expression_closure_type = typename matrix_traits<_Expressioin>::closure_type;
public:
	constexpr MatrixColVector(_expression_closure_type expression, size_t col) : _expression(expression), _col(col) {}

	using base_type::operator();
	constexpr element_type operator()(size_t index)const { return _expression()(index, _col); }
private:
	_expression_closure_type _expression;
	size_t _col = 0;
};
//verify

NGS_MLA_END
