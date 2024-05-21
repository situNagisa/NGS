#pragma once

#include "../bytebit.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

constexpr ::std::size_t byte_to_bit(::std::size_t byte) noexcept
{
	return byte * bit_limit::byte();
}

constexpr ::std::size_t bit_to_byte_floor(::std::size_t bit) noexcept
{
	return bit / bit_limit::byte();
}

constexpr ::std::size_t bit_to_byte_ceil(::std::size_t bit) noexcept
{
	if constexpr (::std::has_single_bit(bit_limit::byte()))
	{
		return NGS_LIB_MODULE_NAME::bit_to_byte_floor(bit) + ((bit & (bit_limit::byte() - 1)) > 0);
	}
	else
	{
		return NGS_LIB_MODULE_NAME::bit_to_byte_floor(bit) + ((bit % bit_limit::byte()) > 0);
	}
}

NGS_LIB_MODULE_END