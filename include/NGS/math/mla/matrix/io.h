#pragma once

#include "NGS/math/mla/config.h"
#include "NGS/math/mla/matrix/expression/concept.h"

NGS_MLA_BEGIN

template<CTemplateFrom<std::basic_ostream> _Ostream, CMatrixExpression _Expression>
_Ostream& operator<<(_Ostream& os, const _Expression& expr) {
	for (size_t row_index = 0; row_index < _Expression::row_count; row_index++)
	{
		os << expr.row(row_index) << NGS_MLA_MATRIX_IO_SEPARATOR;
	}
	return os;
}

NGS_MLA_END