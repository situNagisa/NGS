#pragma once

#include "./constant.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN


constexpr bool is_valid_align(align_t align, align_t default_align_ = 1) {
	return (align == no_align) || (align == default_align) || (::std::has_single_bit(align) && align >= default_align_);
}

NGS_LIB_MODULE_END
