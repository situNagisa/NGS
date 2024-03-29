﻿#pragma once

#include "./defined.h"

NGS_MATH_LA_VECTOR_RANGE_BEGIN

namespace detail
{

	inline constexpr auto input_iterator_callback = [](auto&& range, traits::vectors::index_t index) -> decltype(auto) {
		return input_value_wrapper_t<decltype(range)>(NGS_PP_PERFECT_FORWARD(range), index);
		};

	inline constexpr auto input_or_output_iterator_callback = [](auto&& range, traits::vectors::index_t index) -> decltype(auto) {
		return input_or_output_value_wrapper_t<decltype(range)>(NGS_PP_PERFECT_FORWARD(range), index);
		};

}

template<concepts::vectors::accessible _T>
using input_iterator_t = nboost::stl_interfaces::trivial_random_access_iterator<_T, input_value_wrapper_t<_T>, detail::input_iterator_callback>;

template<concepts::vectors::accessible _T> requires concepts::vectors::assignable<_T, traits::vectors::value_t<_T>>
using input_or_output_iterator_t = nboost::stl_interfaces::trivial_random_access_iterator<_T, input_or_output_value_wrapper_t<_T>, detail::input_or_output_iterator_callback>;

template<concepts::vectors::accessible _T>
using input_reverse_iterator_t = std::reverse_iterator<input_iterator_t<_T>>;

template<concepts::vectors::accessible _T> requires concepts::vectors::assignable<_T, traits::vectors::value_t<_T>>
using input_or_output_reverse_iterator_t = std::reverse_iterator<input_or_output_iterator_t<_T>>;

NGS_MATH_LA_VECTOR_RANGE_END