#pragma once

#include "./defined.h"
#include "./floor.h"

NGS_MATH_BASIC_BEGIN

constexpr auto modulus(cpt::real_number auto dividend,const cpt::real_number auto divisor) {
	return dividend - floor(dividend / divisor) * divisor;
}

NGS_MATH_BASIC_END
