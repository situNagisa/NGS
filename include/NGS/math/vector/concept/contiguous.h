#pragma once

#include "./input.h"

NGS_LIB_MODULE_BEGIN

template<class _V>
concept contiguous_vector = input_vector<_V> && ::std::ranges::contiguous_range<_V>;

NGS_LIB_MODULE_END