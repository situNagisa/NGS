#pragma once

#include "NGS/math/mla/matrix/expression/expression.h"

NGS_MLA_BEGIN

template<CMatrixExpression _Expression>
constexpr auto row(const _Expression& expression, size_t row_index) { return MatrixRowVector<_Expression>(expression, row_index); }
template<CMatrixExpression _Expression>
constexpr auto column(const _Expression& expression, size_t col_index) { return MatrixColVector<_Expression>(expression, col_index); }

NGS_MLA_END
