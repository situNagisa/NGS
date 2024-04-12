#pragma once

#include "../bytebit.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

constexpr ::std::size_t byte_to_bit(::std::size_t byte) noexcept
{
	return byte * byte_bits;
}

constexpr ::std::size_t bit_to_byte_floor(::std::size_t bit) noexcept
{
	return bit / byte_bits;
}

constexpr ::std::size_t bit_to_byte_ceil(::std::size_t bit) noexcept
{
	return NGS_LIB_MODULE_NAME::bit_to_byte_floor(bit) + ((bit % byte_bits) > 0);
}

NGS_LIB_MODULE_END