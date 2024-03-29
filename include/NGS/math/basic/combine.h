﻿#pragma once

#include "./permutate.h"

NGS_MATH_BASIC_BEGIN

constexpr auto combine(size_t subscript, size_t superscript) {
	return permutate(subscript, superscript) / permutate(subscript, superscript);
}

NGS_MATH_BASIC_END
