#pragma once

#include "../value.h"
#include "./input_or_output.h"

NGS_LIB_MODULE_BEGIN

template<class _M, class _E = matrix_value_t<_M>>
concept output_matrix = input_or_output_matrix<_M> && vectors::output_vector<::std::ranges::range_value_t<_M>, _E>;

NGS_LIB_MODULE_END