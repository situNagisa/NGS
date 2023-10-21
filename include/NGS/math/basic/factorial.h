#pragma once

#include "./defined.h"

NGS_MATH_BASIC_BEGIN

constexpr auto factorial(size_t n) {
	size_t result = 1;
	for (size_t i = 1; i <= n; ++i) {
		result *= i;
	}
	return result;
}

NGS_MATH_BASIC_END
