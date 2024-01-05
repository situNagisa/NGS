#pragma once

#include "./value.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

namespace _detail
{
	template<class _L, class _R>
	concept binary_vector_concept =
		input_vector<_L> && input_vector<_R> &&
		accessable_vector<_L> && accessable_vector<_R> &&
		maybe_same_extent<_L, _R>;

	template<class _L, class _R>
	concept binary_vector_operatable = binary_vector_concept<_L, _R>&& operator_vector<_L>&& operator_vector<_R>;
}

template<class _L, class _R> requires _detail::binary_vector_concept<_L, _R>
using add_view = add_value_view<_L, _R>;
template<class _L, class _R> requires _detail::binary_vector_concept<_L, _R>
using subtract_view = subtract_value_view<_L, _R>;

template<class _L, class _R> requires _detail::binary_vector_concept<_L, _R>
constexpr decltype(auto) add(_L&& left, _R&& right) { return NGS_LIB_MODULE_NAME::add_value(NGS_PP_PERFECT_FORWARD(left), NGS_PP_PERFECT_FORWARD(right)); }

template<class _L, class _R> requires _detail::binary_vector_concept<_L, _R>
constexpr decltype(auto) subtract(_L&& left, _R&& right) { return NGS_LIB_MODULE_NAME::subtract_value(NGS_PP_PERFECT_FORWARD(left), NGS_PP_PERFECT_FORWARD(right)); }

NGS_LIB_MODULE_END