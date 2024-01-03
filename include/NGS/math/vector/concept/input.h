#pragma once

#include "./input_or_output.h"

NGS_LIB_MODULE_BEGIN

template<class _V>
concept input_vector = input_or_output_vector<_V>;

NGS_MATH_VECTOR_RECURSE_ANCHOR_CONCEPT_UNARY(input_vector);

NGS_LIB_MODULE_END