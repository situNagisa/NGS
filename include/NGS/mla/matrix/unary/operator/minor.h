﻿#pragma once

#include "NGS/mla/matrix/expression/square.h"
#include "NGS/mla/matrix/unary/unary.h"
#include "NGS/mla/matrix/traits.h"

NGS_MLA_BEGIN

template<CSquareMatrix _Expression>
struct MatrixMinor : SquareMatrix<MatrixMinor<_Expression>, std::integral_constant<size_t, _Expression::row_count>> {
private:
	using base_type = MatrixMinor::self_type;
protected:
	using self_type = MatrixMinor<_Expression>;
public:
	using element_type = typename _Expression::element_type;
private:
	using closure_type = typename matrix_traits<_Expression>::closure_type;
public:
	using base_type::base_type;
	constexpr MatrixMinor(closure_type expression, size_t row_index, size_t col_index)
		: _expression(expression)
		, _row_index(row_index)
		, _col_index(col_index)
	{}


	using base_type::operator();
	constexpr element_type operator()(size_t row_index, size_t col_index)const {
		return _expression()(row_index + (row_index < _row_index), col_index + (col_index < _col_index));
	}
private:
	closure_type _expression;
	size_t _row_index = 0;
	size_t _col_index = 0;
};

template<CSquareMatrix _Expression>
constexpr auto minor(const _Expression& expression, size_t row, size_t column) {
	return MatrixMinor<_Expression>(expression, row, column);
}

NGS_MLA_END