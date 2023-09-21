#pragma once

#include "NGS/math/mla/vector/expression/expression.h"

NGS_MLA_BEGIN

template<CVectorExpression _Vector> requires (_Vector::dimension == 2)
constexpr auto polar_angle(const _Vector& vector) {
	return std::atan2(vector(1), vector(0));
}

NGS_MLA_END
