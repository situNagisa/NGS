#pragma once

#include "./defined.h"

NGS_MATH_BASIC_BEGIN

constexpr auto permutate(size_t subscript, size_t superscript) {
	size_t result = 1;
	for (size_t i = subscript - superscript + 1; i <= subscript; ++i) {
		result *= i;
	}
	return result;
}

NGS_MATH_BASIC_END
