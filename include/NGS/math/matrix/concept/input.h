#pragma once

#include "./input_or_output.h"

NGS_LIB_MODULE_BEGIN

template<class _M>
concept input_matrix = input_or_output_matrix<_M> && vectors::input_vector<_M> && vectors::input_vector<::std::ranges::range_value_t<_M>>;

NGS_LIB_MODULE_END