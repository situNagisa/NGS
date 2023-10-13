#pragma once

#include "./constant.h"

NGS_LAYOUT_BEGIN

constexpr bool is_align(size_t align, size_t default_align_ = 1) {
	return (align == no_align) || (align == default_align) || (std::has_single_bit(align) && align >= default_align_);
}

NGS_LAYOUT_END
