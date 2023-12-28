﻿#pragma once

#include "./size.h"
#include "./concept.h"
#include "./defined.h"

NGS_LIB_BEGIN

constexpr decltype(auto) random_access(input_vector auto&& vector, index_t index)
{
	return *(::std::ranges::begin(vector) + index);
}

NGS_LIB_END
