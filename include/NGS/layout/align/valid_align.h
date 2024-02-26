#pragma once

#include "./concept.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN


constexpr bool is_valid_align(const align auto& align_, ::std::size_t default_align_ = 1)
{
	return (::std::has_single_bit(align_.align()) && align_.align() >= default_align_);
}

NGS_LIB_MODULE_END
