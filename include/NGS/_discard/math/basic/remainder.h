#pragma once

#include "./defined.h"
#include "./fix.h"

NGS_MATH_BASIC_BEGIN

constexpr auto remainder(cpt::real_number auto dividend, const cpt::real_number auto divisor) {
	if (std::is_constant_evaluated()) {
		return dividend - fix(dividend / divisor) * divisor;
	}
	else {
		return std::fmod(dividend, divisor);
	}
}

NGS_MATH_BASIC_END
