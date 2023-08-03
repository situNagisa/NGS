#pragma once

#include "NGS/mla/vector/binary/traits.h"
#include "NGS/mla/scalar/binary/plus.h"

NGS_MLA_BEGIN

template<CVectorExpression _Expression1, CVectorExpression _Expression2>
constexpr vector_binary_scalar_traits_t<_Expression1, _Expression2, ScalarPlusFunctor> operator+(const _Expression1& expr1, const _Expression2& expr2) {
	return vector_binary_scalar_traits_t<_Expression1, _Expression2, ScalarPlusFunctor>(expr1, expr2);
}

NGS_MLA_END
