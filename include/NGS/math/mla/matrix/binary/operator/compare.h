#pragma once

#include "NGS/math/mla/matrix/expression/concept.h"

NGS_MLA_BEGIN

template<CMatrixExpression _Left, CMatrixExpression _Right> requires (_Left::row_count == _Right::row_count && _Left::col_count == _Right::col_count)
constexpr bool compare(const _Left& left, const _Right& right) {
	for (size_t row_index = 0; row_index < _Left::row_count; row_index++)
	{
		for (size_t col_index = 0; col_index < _Left::col_count; col_index++)
		{
			if (left()(row_index, col_index) != right()(row_index, col_index))return false;
		}
	}
	return true;
}
template<CMatrixExpression _Left, CMatrixExpression _Right> requires (_Left::row_count == _Right::row_count && _Left::col_count == _Right::col_count)
constexpr bool operator==(const _Left& left, const _Right& right) { return compare(left, right); }

NGS_MLA_END
