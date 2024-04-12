#pragma once

#include "./defined.h"

NGS_LIB_BEGIN

enum class granularity
{
	bit = 0,
	page = 1
};

constexpr ::std::uint32_t granularity_factor(granularity granularity)
{
	return granularity == granularity::page ? 0x1000 : 0x1;
}

NGS_LIB_END