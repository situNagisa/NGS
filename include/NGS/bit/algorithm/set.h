#pragma once

#include "../bitset.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

constexpr decltype(auto) set(bitsets::bitset auto bitset,::std::size_t pos)
{
	using result_type = decltype(bitset);

	return static_cast<result_type>(bitset | (static_cast<result_type>(1) << pos));
}

constexpr decltype(auto) reset(bitsets::bitset auto bitset,::std::size_t pos)
{
	using result_type = decltype(bitset);

	return static_cast<result_type>(bitset & ~(static_cast<result_type>(1) << pos));
}

constexpr bool test(bitsets::bitset auto bitset,::std::size_t pos)
{
	return bitset & (static_cast<decltype(bitset)>(1) << pos);
}

constexpr decltype(auto) set(bitsets::bitset auto bitset,::std::size_t pos,bool value)
{
	return value ? NGS_LIB_MODULE_NAME::set(bitset,pos) : NGS_LIB_MODULE_NAME::reset(bitset,pos);
}

NGS_LIB_MODULE_END