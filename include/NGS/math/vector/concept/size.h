#pragma once

#include "./input_or_output.h"

NGS_LIB_MODULE_BEGIN

template<class _V>
concept sized_vector = input_or_output_vector<_V> && ::std::ranges::sized_range<_V>;

NGS_LIB_MODULE_END