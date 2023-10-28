#pragma once

#include "NGS/math/vector/concept.h"

NGS_MATH_VECTOR_BEGIN

template<functor::expression _Vector,space::CAxis _Major = space::x,space::CAxis _Minor = space::y>
constexpr auto principal_angle(const _Vector& vector) {
	return std::atan2(vector(_Minor::dimension), vector(_Major::dimension));
}

NGS_MATH_VECTOR_END