#pragma once

#include "./defined.h"

NGS_LIB_MODULE_BEGIN

enum class page_size
{
	_4kb = 0,
	_4mb = 1,
};

constexpr ::std::size_t factor(page_size size)
{
	using namespace bits::literals;
	return static_cast<::std::size_t>(size == page_size::_4mb ? 4_mb : 4_kb);
}

NGS_LIB_MODULE_END
