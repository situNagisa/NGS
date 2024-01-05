#pragma once

#include "./depth.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

template<class _V>
concept input_or_output_vector = generalized_vector<_V> && ::std::ranges::range<_V>;

template<class _V>
concept input_vector = input_or_output_vector<_V> && ::std::ranges::input_range<_V>;

template<class _V, class _E = ::std::conditional_t<input_or_output_vector<_V>, ::std::ranges::range_value_t<_V>, void>>
concept output_vector = input_or_output_vector<_V> && ::std::ranges::output_range<_V, _E>;

NGS_MATH_VECTOR_RECURSE_ANCHOR_CONCEPT_UNARY(input_or_output_vector);
NGS_MATH_VECTOR_RECURSE_ANCHOR_CONCEPT_UNARY(input_vector);

NGS_LIB_MODULE_END