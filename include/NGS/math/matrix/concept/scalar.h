#pragma once

#include "./input_or_output.h"

NGS_LIB_MODULE_BEGIN

template<class _M>
concept scalar_matrix = input_or_output_matrix<_M> && vectors::scalar_vector_at<_M, 1>;

NGS_LIB_MODULE_END