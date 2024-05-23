#pragma once

#include "../concept.h"
#include "../algorithm.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

constexpr decltype(auto) operator&(concepts::range auto&& left, concepts::range auto&& right)
{
	return algorithm::bit_and(NGS_PP_PERFECT_FORWARD(left), NGS_PP_PERFECT_FORWARD(right));
}

constexpr decltype(auto) operator|(concepts::range auto&& left, concepts::range auto&& right)
{
	return algorithm::bit_or(NGS_PP_PERFECT_FORWARD(left), NGS_PP_PERFECT_FORWARD(right));
}

constexpr decltype(auto) operator^(concepts::range auto&& left, concepts::range auto&& right)
{
	return algorithm::bit_xor(NGS_PP_PERFECT_FORWARD(left), NGS_PP_PERFECT_FORWARD(right));
}

constexpr decltype(auto) operator~(concepts::range auto&& range)
{
	return algorithm::bit_not(NGS_PP_PERFECT_FORWARD(range));
}

NGS_LIB_MODULE_END