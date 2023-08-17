#pragma once

#include "NGS/math/mla/scalar/unary.h"
#include "NGS/math/mla/matrix/unary/unary.h"

NGS_MLA_BEGIN

struct NGS_API _Negate {
	constexpr _Negate() = default;
	template<CMatrixExpression _Expression>
	constexpr auto operator()(const _Expression& expression) const {
		return matrix_unary_scalar_functor_t<_Expression, ScalarNegateFunctor>(expression);
	}
};
//inline constexpr _Negate negate{};

template<CMatrixExpression _Expression>
constexpr auto negate(const _Expression& expression) {
	return matrix_unary_scalar_functor_t<_Expression, ScalarNegateFunctor>(expression);
}

template<CMatrixExpression _Expression>
constexpr auto operator-(const _Expression& expression) { return negate(expression); }

NGS_MLA_END
