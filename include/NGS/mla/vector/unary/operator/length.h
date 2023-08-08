#pragma once

#include "NGS/mla/vector/unary/traits.h"
#include "NGS/mla/scalar/unary/negate.h"

NGS_MLA_BEGIN

template<CVectorExpression _Expression>
constexpr typename _Expression::expression_type::element_type length_squared(const _Expression& expr) {
	typename _Expression::expression_type::element_type result = 0;
	for (size_t i = 0; i < _Expression::expression_type::dimension; i++)
	{
		result += expr()(i) * expr()(i);
	}
	return result;
}
template<CVectorExpression _Expression>
constexpr auto length(const _Expression& expr) { return std::sqrt(length_squared(expr)); }

NGS_MLA_END
