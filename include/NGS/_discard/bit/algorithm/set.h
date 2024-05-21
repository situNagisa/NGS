#pragma once

#include "../bitset.h"
#include "./bit_of.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

namespace _detail
{
	template<class Bitset>
	constexpr auto local_position(::std::size_t pos)
	{
		using bitset_type = Bitset;

		constexpr auto size = NGS_LIB_MODULE_NAME::bit_of<bitset_type>();
		constexpr auto uint = NGS_LIB_MODULE_NAME::bit_of<::std::ranges::range_value_t<bitset_type>>();
		auto index = pos / uint;
		auto offset = [pos]
			{
				if constexpr (::std::has_single_bit(uint))
				{
					return pos & (uint - 1);
				}
				else
				{
					return pos % uint;
				}
			}();

		return ::std::make_pair(index, offset);
	}
}

constexpr decltype(auto) set(bitsets::bitset auto& bitset,::std::size_t pos)
{
	using bitset_type = decltype(bitset);

	if constexpr (bitsets::bit_fundamental<bitset_type>)
	{
		bitset |= (static_cast<type_traits::object_t<bitset_type>>(1) << pos);
	}
	else if constexpr (bitsets::bit_array<bitset_type>)
	{
		auto[index, offset] = _detail::local_position<bitset_type>(pos);

		return NGS_LIB_MODULE_NAME::set(bitset[index], offset);
	}
}

constexpr decltype(auto) reset(bitsets::bitset auto& bitset,::std::size_t pos)
{
	using bitset_type = decltype(bitset);

	if constexpr (bitsets::bit_fundamental<bitset_type>)
	{
		bitset &= ~(static_cast<type_traits::object_t<bitset_type>>(1) << pos);
	}
	else if constexpr (bitsets::bit_array<bitset_type>)
	{
		auto [index, offset] = _detail::local_position<bitset_type>(pos);

		return NGS_LIB_MODULE_NAME::reset(bitset[index], offset);
	}
}

constexpr bool test(const bitsets::bitset auto& bitset,::std::size_t pos)
{
	using bitset_type = decltype(bitset);

	if constexpr (bitsets::bit_fundamental<bitset_type>)
	{
		return bitset & (static_cast<type_traits::object_t<bitset_type>>(1) << pos);
	}
	else if constexpr (bitsets::bit_array<bitset_type>)
	{
		auto [index, offset] = _detail::local_position<bitset_type>(pos);

		return NGS_LIB_MODULE_NAME::test(bitset[index], offset);
	}
	else
	{
		return false;
	}
}

constexpr decltype(auto) set(bitsets::bitset auto&& bitset, ::std::size_t pos, bool value)
{
	return value ? NGS_LIB_MODULE_NAME::set(NGS_PP_PERFECT_FORWARD(bitset), pos) : NGS_LIB_MODULE_NAME::reset(NGS_PP_PERFECT_FORWARD(bitset), pos);
}

enum class shift_direction
{
	left,
	right
};

template<shift_direction Direction>
constexpr decltype(auto) shift(bitsets::bitset auto& bitset, ::std::size_t shift)
{
	using bitset_type = decltype(bitset);

	if constexpr (bitsets::bit_fundamental<bitset_type>)
	{
		if constexpr (Direction == shift_direction::left)
		{
			bitset <<= shift;
		}
		else
		{
			bitset >>= shift;
		}
	}
	else if constexpr (bitsets::bit_array<bitset_type>)
	{
		if constexpr (Direction == shift_direction::left)
		{
			for(::std::size_t i = 0; i < NGS_LIB_MODULE_NAME::bit_of<bitset_type>() - shift; i++)
			{
				::std::size_t pos = NGS_LIB_MODULE_NAME::bit_of<bitset_type>() - 1 - i;
				NGS_LIB_MODULE_NAME::set(bitset, pos, NGS_LIB_MODULE_NAME::test(bitset, pos - shift));
			}
			for (::std::size_t i = 0; i < shift; i++)
			{
				::std::size_t pos = i;
				NGS_LIB_MODULE_NAME::reset(bitset, pos);
			}
		}
		else
		{
			for (::std::size_t i = 0; i < NGS_LIB_MODULE_NAME::bit_of<bitset_type>() - shift; i++)
			{
				::std::size_t pos = i;
				NGS_LIB_MODULE_NAME::set(bitset, pos, NGS_LIB_MODULE_NAME::test(bitset, pos + shift));
			}
			for (::std::size_t i = 0; i < shift; i++)
			{
				::std::size_t pos = NGS_LIB_MODULE_NAME::bit_of<bitset_type>() - 1 - i;
				NGS_LIB_MODULE_NAME::reset(bitset, pos);
			}
		}
	}
}

NGS_LIB_MODULE_END