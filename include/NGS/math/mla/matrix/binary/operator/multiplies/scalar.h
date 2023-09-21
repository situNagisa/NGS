#pragma once

#include "NGS/math/mla/matrix/binary/binary.h"
#include "NGS/math/mla/scalar/binary.h"
#include "NGS/math/mla/matrix/expression/container.h"
#include "NGS/math/mla/matrix/expression/scalar.h"
#include "NGS/math/mla/vector/binary.h"
#include "NGS/math/mla/vector/expression/concept.h"
#include "NGS/math/mla/matrix/unary/operator/access.h"
#include "NGS/math/mla/matrix/expression/vector.h"
#include "NGS/math/mla/scalar/expression/concept.h"
#include "NGS/math/mla/vector/unary/operator/homogen.h"

NGS_MLA_BEGIN

template<CMatrixExpression _Expression, CScalarExpression _ScalarExpression>
constexpr auto multiplies_scalar(const _Expression& expression, _ScalarExpression scalar) {
	using scalar_t = matrix_scalar_expression_t<matrix_traits<_Expression>::row_count, matrix_traits<_Expression>::col_count, _ScalarExpression>;
	using binary_t = matrix_binary_scalar_t<_Expression, scalar_t, ScalarMultipliesFunctor>;
	return binary_t(expression, scalar_t(scalar));
}

template<CMatrixExpression _Expression, CScalarExpression _ScalarExpression>
constexpr auto multiplies_scalar(_ScalarExpression scalar, const _Expression& expression) {
	using scalar_t = matrix_scalar_expression_t<matrix_traits<_Expression>::row_count, matrix_traits<_Expression>::col_count, _ScalarExpression>;
	using binary_t = matrix_binary_scalar_t<scalar_t, _Expression, ScalarMultipliesFunctor>;
	return binary_t(scalar_t(scalar), expression);
}
template<CMatrixExpression _Expression, CScalarExpression _ScalarExpression>
constexpr auto operator*(_ScalarExpression scalar, const _Expression& expression) { return multiplies_scalar(scalar, expression); }
template<CMatrixExpression _Expression, CScalarExpression _ScalarExpression>
constexpr auto operator*(const _Expression& expression, _ScalarExpression scalar) { return multiplies_scalar(expression, scalar); }

template<CMatrixContainer _Container, CScalarExpression _ScalarExpression>
_Container& multiplies_assign(_Container& container, _ScalarExpression scalar) { return container.assign(multiplies_scalar(container, scalar)); }
template<CMatrixContainer _Container, CScalarExpression _ScalarExpression>
_Container& operator*=(_Container& container, _ScalarExpression scalar) { return multiplies_assign(container, scalar); }


NGS_MLA_END
