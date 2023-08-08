#pragma once

#include "NGS/math/mla/scalar/unary.h"
#include "NGS/math/mla/matrix/unary/unary.h"

NGS_MLA_BEGIN

template<CMatrixExpression _Expression>
constexpr matrix_unary_scalar_functor_t<_Expression, ScalarNegateFunctor> negate(const _Expression& expression) {
	return matrix_unary_scalar_functor_t<_Expression, ScalarNegateFunctor>(expression);
}
template<CMatrixExpression _Expression>
constexpr auto operator-(const _Expression& expression) { return negate(expression); }

NGS_MLA_END
