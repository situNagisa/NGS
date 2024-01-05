#pragma once

#include "NGS/math/mla/config.h"
#include "NGS/math/mla/matrix/expression/concept.h"

NGS_BEGIN

template<mla::CMatrixExpression _Expression>
constexpr std::string to_string(const _Expression& expr) {
	std::string str;
	for (size_t row_index = 0; row_index < _Expression::row_count; row_index++)
	{
		str += to_string(expr.row(row_index));
		str += NGS_MLA_MATRIX_IO_SEPARATOR;
	}
	return str;
}

NGS_END