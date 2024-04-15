#pragma once

#include "./defined.h"

NGS_LIB_BEGIN

enum class granularity : ::std::uint8_t
{
	bit = 0,
	page = 1
};

constexpr ::std::size_t granularity_factor(granularity granularity)
{
	using namespace bits::literals;
	return static_cast<::std::size_t>(granularity == granularity::page ? 4_kb : 1_b);
}

constexpr ::std::size_t page_size(granularity granularity)
{
	using namespace bits::literals;
	return static_cast<::std::size_t>(4_kb * granularity_factor(granularity));
}

NGS_LIB_END