#pragma once

#include "./defined.h"

NGS_MATH_LA_VECTOR_RANGE_BEGIN

template<concepts::vectors::accessible _T>
using input_value_wrapper_t = wrappers::input_wrapper<adapters::vectors::access, std::tuple<_T&, traits::vectors::index_t>>;

template<class _T>requires concepts::vectors::assignable<_T, traits::vectors::value_t<_T>>
using output_value_wrapper_t = wrappers::output_wrapper<adapters::vectors::assign, std::tuple<_T&, traits::vectors::index_t>>;

template<concepts::vectors::accessible _T>requires concepts::vectors::assignable<_T, traits::vectors::value_t<_T>>
using input_or_output_value_wrapper_t = wrappers::input_or_output_wrapper<adapters::vectors::access, adapters::vectors::assign, std::tuple<_T&, traits::vectors::index_t>>;

NGS_MATH_LA_VECTOR_RANGE_END