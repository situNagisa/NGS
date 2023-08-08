#pragma once

#include "NGS/math/mla/matrix/expression/expression.h"

NGS_MLA_BEGIN

template<class _Expression>
concept CSquareMatrix = requires() {
	requires CMatrixExpression<_Expression>;
	requires _Expression::row_count == _Expression::col_count;
};

template<ccpt::CRPT<CMatrixExpression<>> _Expression, ccpt::UInt _Dim>
struct SquareMatrix : MatrixExpression<_Expression> {
private:
	using base_type = SquareMatrix::self_type;
protected:
	using self_type = SquareMatrix<_Expression, _Dim>;
public:
	constexpr static size_t row_count = _Dim::value;
	constexpr static size_t col_count = _Dim::value;
	constexpr static size_t element_count = row_count * col_count;
};

NGS_MLA_END
