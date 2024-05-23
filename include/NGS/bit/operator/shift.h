#pragma once

#include "../concept.h"
#include "../algorithm.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

constexpr decltype(auto) operator<<(concepts::range auto&& left, ::std::integral auto shift)
{
	return algorithm::left_shift(NGS_PP_PERFECT_FORWARD(left), shift);
}

constexpr decltype(auto) operator>>(concepts::range auto&& left, ::std::integral auto shift)
{
	return algorithm::right_shift(NGS_PP_PERFECT_FORWARD(left), shift);
}

NGS_LIB_MODULE_END