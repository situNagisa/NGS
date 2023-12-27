#pragma once

#include "./input_or_output.h"

NGS_LIB_MODULE_BEGIN

template<class _V, class _E = ::std::conditional_t<input_or_output_vector<_V>, ::std::ranges::range_value_t<_V>, void>>
concept output_vector = input_or_output_vector<_V> && ::std::ranges::output_range<_V, _E>;

NGS_LIB_MODULE_END