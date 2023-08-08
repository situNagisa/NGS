#pragma once

#include "NGS/mla/vector/unary/traits.h"
#include "NGS/mla/scalar/unary/negate.h"

NGS_MLA_BEGIN

template<CVectorExpression _Expression>
constexpr auto negate(const _Expression& expr) { return vector_unary_scalar_traits_t<_Expression, ScalarNegateFunctor>(expr); }
template<CVectorExpression _Expression>
constexpr auto operator-(const _Expression& expr) { return negate(expr); }

NGS_MLA_END
