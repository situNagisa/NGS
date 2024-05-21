#pragma once

#include "../concept.h"
#include "./bit_of.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN


enum class shift_direction
{
	left,
	right
};

template<shift_direction Direction>
constexpr decltype(auto) shift(concepts::output_range auto& bitset, ::std::size_t shift)
{
	if constexpr (Direction == shift_direction::left)
	{
		NGS_LIB_MODULE_NAME::shift<shift_direction::right>(bitset | ::std::views::reverse, shift);
	}
	else
	{
		auto shift_size = ::std::ranges::size(bitset) - shift;

		auto&& a = ::std::views::all(bitset);
		auto&& m = NGS_PP_PERFECT_FORWARD(bitset);
		auto t = bitset | ::std::views::take(shift_size);
		auto d = bitset | ::std::views::drop(shift);
		auto z = ::std::views::zip(t, d);

		for (auto&& [destination, source] : ::std::views::zip(
			bitset | ::std::views::take(shift_size),
			bitset | ::std::views::drop(shift)
		))
		{
			destination = source;
		}
		for(auto&& destination : bitset | ::std::views::drop(shift_size))
		{
			destination = false;
		}
	}
}

constexpr decltype(auto) left_shift(concepts::output_range auto& bitset, ::std::size_t shift)
{
	return NGS_LIB_MODULE_NAME::shift<shift_direction::left>(bitset, shift);
}

constexpr decltype(auto) right_shift(concepts::output_range auto& bitset, ::std::size_t shift)
{
	return NGS_LIB_MODULE_NAME::shift<shift_direction::right>(bitset, shift);
}

NGS_LIB_MODULE_END