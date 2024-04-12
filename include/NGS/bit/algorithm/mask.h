#pragma once

#include "../bitset.h"
#include "./bit_of.h"
#include "./bit_byte.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

template<bitsets::bit_integral Result = ::std::uint32_t>
constexpr auto mask(::std::size_t bit)
{
	[[unlikely]]
	if (bit > NGS_LIB_MODULE_NAME::bit_of<Result>())
		return static_cast<Result>(-1);

	return (static_cast<Result>(1) << bit) - 1;
}

template<bitsets::bit_integral Result = ::std::uint32_t>
constexpr auto mask(::std::size_t bit, ::std::size_t begin)
{
	return NGS_LIB_MODULE_NAME::mask<Result>(bit) << begin;
}

NGS_LIB_MODULE_END