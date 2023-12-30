#pragma once

#include "../concept.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

constexpr decltype(auto) access(contiguous_vector auto&& vector, index_t index)
{
	if constexpr (requires{ NGS_PP_PERFECT_FORWARD(vector)[index]; })
		return NGS_PP_PERFECT_FORWARD(vector)[index];
	else
		return ::std::ranges::data(vector)[index];
}

NGS_LIB_MODULE_END