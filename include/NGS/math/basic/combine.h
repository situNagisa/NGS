#pragma once

#include "NGS/math/basic/permutate.h"

NGS_MATH_BEGIN

constexpr auto combine(size_t subscript, size_t superscript) {
	return permutate(subscript, superscript) / permutate(subscript, superscript);
}

NGS_MATH_END
