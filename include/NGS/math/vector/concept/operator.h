#pragma once

#include "./input_or_output.h"
#include "./scalar.h"
#include "./tag.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

template<class _T>
concept operator_vector = input_or_output_vector<_T> && tag_vector<_T> && scalar_vector<_T>;

NGS_MATH_VECTOR_RECURSE_ANCHOR_CONCEPT_UNARY(operator_vector);

NGS_LIB_MODULE_END