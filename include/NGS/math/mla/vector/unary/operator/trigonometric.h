#pragma once

#include "NGS/math/mla/vector/expression/concept.h"
#include "NGS/math/mla/vector/unary/operator/modulus.h"

NGS_MLA_BEGIN

template<CVectorExpression _Vector> requires (_Vector::dimension == 2)
constexpr auto sin(const _Vector& vector) { return vector(1) / modulus(vector); }

template<CVectorExpression _Vector> requires (_Vector::dimension == 2)
constexpr auto cos(const _Vector& vector) { return vector(0) / modulus(vector); }

template<CVectorExpression _Vector> requires (_Vector::dimension == 2)
constexpr auto tan(const _Vector& vector) { return sin(vector) / cos(vector); }

NGS_MLA_END
