#pragma once

#include "NGS/math/mla/vector/expression/concept.h"

NGS_MLA_BEGIN

template<CVectorExpression _Expression1, CVectorExpression _Expression2> requires (_Expression1::dimension == _Expression2::dimension)
constexpr bool compare(const _Expression1& expr1, const _Expression2& expr2) {
	for (size_t i = 0; i < _Expression1::dimension; ++i) {
		if (expr1()(i) != expr2()(i))return false;
	}
	return true;
}
template<CVectorExpression _Expression1, CVectorExpression _Expression2> requires (_Expression1::dimension == _Expression2::dimension)
constexpr bool operator==(const _Expression1& expr1, const _Expression2& expr2) { return compare(expr1, expr2); }

NGS_MLA_END
