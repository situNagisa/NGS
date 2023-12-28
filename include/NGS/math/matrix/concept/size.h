#pragma once

#include "./input_or_output.h"

NGS_LIB_MODULE_BEGIN

template<class _M>
concept sized_matrix = input_or_output_matrix<_M> && vectors::sized_vector<_M> && vectors::sized_vector<::std::ranges::range_value_t<_M>>;

NGS_LIB_MODULE_END