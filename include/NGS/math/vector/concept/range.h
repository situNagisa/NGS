#pragma once

#include "./io.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

template<class _V>
concept random_access_vector = input_vector<_V> && ::std::ranges::random_access_range<_V>;

template<class _V>
concept contiguous_vector = random_access_vector<_V> && ::std::ranges::contiguous_range<_V>;

template<class _V>
concept sized_vector = input_or_output_vector<_V> && ::std::ranges::sized_range<_V>;

NGS_MATH_VECTOR_RECURSE_ANCHOR_CONCEPT_UNARY(random_access_vector);
NGS_MATH_VECTOR_RECURSE_ANCHOR_CONCEPT_UNARY(contiguous_vector);
NGS_MATH_VECTOR_RECURSE_ANCHOR_CONCEPT_UNARY(sized_vector);

NGS_LIB_MODULE_END