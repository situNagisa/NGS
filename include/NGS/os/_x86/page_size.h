#pragma once

#include "./defined.h"

NGS_LIB_BEGIN

enum class page_size
{
	_4kb = 0,
	_4mb = 1,
};

constexpr ::std::size_t page_size_factor(page_size granularity)
{
	using namespace bits::literals;
	return static_cast<::std::size_t>(granularity == page_size::_4mb ? 4_mb : 4_kb);
}

NGS_LIB_END
