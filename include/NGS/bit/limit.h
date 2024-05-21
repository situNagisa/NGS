#pragma once

#include "./defined.h"

NGS_LIB_BEGIN

struct bit_limit
{
	constexpr static ::std::size_t byte() { return CHAR_BIT; }
	constexpr static ::std::size_t unsigned_max() { return sizeof(::std::uintmax_t) * byte(); }
};

NGS_LIB_END