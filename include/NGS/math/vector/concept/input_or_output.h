#pragma once

#include "../anchor.h"
#include "../value.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

template<class _V>
concept input_or_output_vector = ::std::ranges::random_access_range<_V>;

NGS_MATH_VECTOR_RECURSE_ANCHOR_CONCEPT_UNARY(input_or_output_vector);

NGS_LIB_MODULE_END