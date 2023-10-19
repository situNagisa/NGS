#pragma once

#include "NGS/math/mla/matrix/expression/expression.h"

NGS_MLA_BEGIN

NGS_MLA_CONCEPT_WITH_DEFINE_DEFAULT_EXT(CMatrixSquare,is_square_matrix,
	CMatrixExpression,
	requires() {
	requires _Type::row_count == _Type::col_count;
});

template<ccpt::CRPT<(bool)CMatrixExpression<>> _Expression, ccpt::UInt _Dim>
struct NGS_API SquareMatrix : MatrixExpression<_Expression> {
	NGS_MPL_ENVIRON(SquareMatrix);
public:
	constexpr static size_t row_count = _Dim::value;
	constexpr static size_t col_count = _Dim::value;
	constexpr static size_t element_count = row_count * col_count;
};

NGS_MLA_END
