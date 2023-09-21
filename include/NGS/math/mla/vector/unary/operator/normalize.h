#pragma once

#include "NGS/math/mla/vector/expression/concept.h"
#include "NGS/math/mla/vector/unary/operator/modulus.h"
#include "NGS/math/mla/vector/binary/operator/basic.h"

NGS_MLA_BEGIN

template<CVectorExpression _Expression>
constexpr auto normalize(const _Expression& expr) { return divides_scalar(expr, modulus(expr)); }

NGS_MLA_END
