#pragma once

#include "../channel.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

template<channels::arithmetic_channel Channel,::std::size_t Offset>
struct primary_channel : Channel
{
	constexpr static ::std::size_t bit_offset() { return Offset; }
};

NGS_LIB_MODULE_END