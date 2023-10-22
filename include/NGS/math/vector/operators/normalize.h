#pragma once

#include "../expression.h"
#include "./arithmetic.h"
#include "./norm.h"

NGS_MATH_VECTOR_BEGIN

template<functor::expression _Vector>
constexpr auto normalize(const _Vector& expr) { return divide(expr, norm(expr)); }


NGS_MATH_VECTOR_END