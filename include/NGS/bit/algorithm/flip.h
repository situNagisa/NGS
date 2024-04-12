#pragma once

#include "../bitset.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

constexpr decltype(auto) flip(bitsets::bitset auto bitset, ::std::size_t index) noexcept
{
	using result_type = decltype(bitset);
	return bitset ^ (static_cast<result_type>(1) << index);
}

constexpr decltype(auto) flip(bitsets::bitset auto bitset) noexcept
{
	return ~bitset;
}

NGS_LIB_MODULE_END