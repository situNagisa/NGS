#pragma once

#include "../bitset.h"
#include "./mask.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

constexpr decltype(auto) span_value(bitsets::bitset auto bitset, ::std::size_t begin, ::std::size_t size) noexcept
{
	using result_type = decltype(bitset);
	return static_cast<result_type>((bitset >> begin) & NGS_LIB_MODULE_NAME::mask<result_type>(size));
}

NGS_LIB_MODULE_END