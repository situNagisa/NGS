#pragma once

#include "NGS/math/mla/matrix/expression/concept.h"
#include "NGS/math/mla/matrix/expression/expression.h"


NGS_MLA_BEGIN

template<CMatrixExpression _Expression,
	ccpt::uint _OffsetRow = std::integral_constant<size_t, 0>,
	ccpt::uint _OffsetCol = std::integral_constant<size_t, 0>,
	ccpt::uint _Dimension = std::integral_constant<size_t, _Expression::row_count>
>requires requires() {
	requires _OffsetRow::value + _Dimension::value <= _Expression::row_count;
	requires _OffsetCol::value + _Dimension::value <= _Expression::col_count;
}
struct NGS_API MatrixView : MatrixExpression<MatrixView<_Expression, _OffsetRow, _OffsetCol, _Dimension>> {
	NGS_MPL_ENVIRON(MatrixView);
public:
	using element_type = typename _Expression::element_type;

	constexpr static size_t dimension = _Dimension::value;
	constexpr static size_t row_count = _Expression::row_count;
	constexpr static size_t col_count = _Expression::col_count;
	constexpr static size_t element_count = row_count * col_count;
	constexpr static size_t complexity = _Expression::complexity + 1;

	constexpr static size_t offset_row = _OffsetRow::value;
	constexpr static size_t offset_col = _OffsetCol::value;
private:
	using closure_type = typename matrix_traits<_Expression>::closure_type;

public:

	constexpr explicit MatrixView(closure_type expression)
		: _expression(expression)
	{}

	constexpr element_type operator()(size_t row_index, size_t col_index)const {
		return _expression()(row_index + offset_row, col_index + offset_col);
	}

private:
	closure_type _expression;
};

template<CMatrixExpression _Expression, size_t _OffsetRow = 0, size_t _OffsetCol = 0, size_t _Dimension = _Expression::row_count>
using matrix_view_t = MatrixView<_Expression,
	std::integral_constant<size_t, _OffsetRow>,
	std::integral_constant<size_t, _OffsetCol>,
	std::integral_constant<size_t, _Dimension>
>;

NGS_MLA_END
