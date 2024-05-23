#pragma once

#include "../concept.h"
#include "./size.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

constexpr decltype(auto) set(concepts::bit_operatable auto& bitset, ::std::integral auto pos) noexcept
//	requires ::std::constructible_from<type_traits::naked_t<decltype(bitset)>, decltype(1 << pos)>
{
	if constexpr (requires{ bitset |= static_cast<type_traits::naked_t<decltype(bitset)>>(1 << pos); })
	{
		bitset |= static_cast<type_traits::naked_t<decltype(bitset)>>(1 << pos);
	}
	else
	{
		bitset = bitset | static_cast<type_traits::naked_t<decltype(bitset)>>(1 << pos);
	}
	
}

constexpr decltype(auto) reset(concepts::bit_operatable auto& bitset, ::std::integral auto pos) noexcept
//	requires ::std::constructible_from<type_traits::naked_t<decltype(bitset)>, decltype(~(1 << pos))>
{
	if constexpr (requires{ bitset &= static_cast<type_traits::naked_t<decltype(bitset)>>(~(1 << pos)); })
	{
		bitset &= static_cast<type_traits::naked_t<decltype(bitset)>>(~(1 << pos));
	}
	else
	{
		bitset = bitset & static_cast<type_traits::naked_t<decltype(bitset)>>(~(1 << pos));
	}
}

constexpr decltype(auto) flip(concepts::bit_operatable auto& bitset, ::std::integral auto pos) noexcept
//	requires ::std::constructible_from<type_traits::naked_t<decltype(bitset)>, decltype(1 << pos)>
{
	if constexpr (requires{ bitset ^= static_cast<type_traits::naked_t<decltype(bitset)>>(1 << pos); })
	{
		bitset ^= static_cast<type_traits::naked_t<decltype(bitset)>>(1 << pos);
	}
	else
	{
		bitset = bitset ^ static_cast<type_traits::naked_t<decltype(bitset)>>(1 << pos);
	}
}

constexpr bool test(const concepts::bit_operatable auto& bitset, ::std::integral auto pos)
//	requires ::std::convertible_to<decltype(1 << pos), type_traits::naked_t<decltype(bitset)>>
{
	return static_cast<bool>(bitset & static_cast<type_traits::naked_t<decltype(bitset)>>(1 << pos));
}

template<class Result = ::std::uint32_t>
constexpr Result mask(::std::integral auto size)
	requires ::std::constructible_from<Result, decltype(1 << size)>
{
	using shift_type = decltype(1 << size);

	[[unlikely]]
	if (size > NGS_LIB_MODULE_NAME::static_size<Result>())
		return { static_cast<shift_type>(-1) };

	return { static_cast<shift_type>((1 << size) - 1) };
}

template<class Result = ::std::uint32_t>
constexpr decltype(auto) mask(::std::integral auto offset, ::std::integral auto size)
	requires ::std::constructible_from<Result, decltype(1 << size)>
{
	return NGS_LIB_MODULE_NAME::mask<Result>(size) << offset;
}

NGS_LIB_MODULE_END