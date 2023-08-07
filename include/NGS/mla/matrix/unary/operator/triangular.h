﻿#pragma once

#include "NGS/mla/matrix/expression/triangular.h"
#include "NGS/mla/matrix/expression/square.h"


NGS_MLA_BEGIN

template<CMatrixExpression _Expression,
	CMatrixTriangularTag _Category,
	ccpt::UInt _OffsetRow = std::integral_constant<size_t, 0>,
	ccpt::UInt _OffsetCol = std::integral_constant<size_t, 0>,
	ccpt::UInt _Dimension = std::integral_constant<size_t, _Expression::row_count>
>requires requires() {
	requires CSquareMatrix<_Expression>;
	requires _OffsetRow::value + _Dimension::value <= _Expression::row_count;
	requires _OffsetCol::value + _Dimension::value <= _Expression::col_count;
}
struct TriangularMatrixAdapter : MatrixExpression<TriangularMatrixAdapter<_Expression, _Category, _OffsetRow, _OffsetCol,_Dimension>> {
private:
	using base_type = TriangularMatrixAdapter::self_type;
protected:
	using self_type = TriangularMatrixAdapter<_Expression, _Category, _OffsetRow, _OffsetCol, _Dimension>;
public:
	using element_type = typename _Expression::element_type;
	using triangular_category = _Category;

	constexpr static size_t dimension = _Dimension::value;
	constexpr static size_t row_count = dimension;
	constexpr static size_t col_count = dimension;
	constexpr static size_t element_count = row_count * col_count;
	constexpr static size_t complexity = _Expression::complexity + 1;

	constexpr static size_t offset_row = _OffsetRow::value;
	constexpr static size_t offset_col = _OffsetCol::value;
private:
	using closure_type = typename matrix_traits<_Expression>::closure_type;

public:

	constexpr TriangularMatrixAdapter(closure_type expression)
		: _expression(expression)
	{}

	constexpr element_type operator()(size_t row_index, size_t col_index)const {
		if (!triangular_category::has_element(row_index + offset_row, col_index + offset_col, row_count, col_count))
			return element_type(0);
		return _expression()(row_index + offset_row, col_index + offset_col);
	}

private:
	closure_type _expression;
};

template<CMatrixExpression _Expression,CMatrixTriangularTag _Category = tag::upper,size_t _OffsetRow = 0,size_t _OffsetCol = 0,size_t _Dimension = _Expression::row_count>
using triangular_matrix_view_t = TriangularMatrixAdapter<
	_Expression, _Category, 
	std::integral_constant<size_t, _OffsetRow>,
	std::integral_constant<size_t, _OffsetCol>,
	std::integral_constant<size_t,_Dimension>
>;

NGS_MLA_END