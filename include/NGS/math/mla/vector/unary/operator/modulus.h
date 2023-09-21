#pragma once

#include "NGS/math/mla/vector/expression/concept.h"
#include "NGS/math/mla/scalar/expression/concept.h"
#include "NGS/math/mla/vector/traits.h"

NGS_MLA_BEGIN

template<CVectorExpression _Expression>
constexpr auto modulus_squared(const _Expression& expr) {
	using element_type = typename vector_traits<_Expression>::element_type;
	element_type result = 0;
	for (size_t i = 0; i < _Expression::expression_type::dimension; i++)
	{
		result += expr()(i) * expr()(i);
	}
	return result;
}
template<CVectorExpression _Expression>
constexpr auto modulus(const _Expression& expr) { return std::sqrt(modulus_squared(expr)); }

NGS_MLA_END
