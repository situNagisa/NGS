#pragma once

#include "./expression.h"

NGS_MATH_LA_VECTOR_CONCEPT_BEGIN

using adapters::vectors::assignable;
using adapters::vectors::callable_contain;
using adapters::vectors::copyable;

template<class _T, class _N = type_traits::naked_t<_T>>
concept container = expression<_T> && assignable<_N, traits::vectors::value_t<_N>>;

template <class _T>
concept output_wrapper = container<_T> && assignable<_T, traits::vectors::value_t<_T>>;

template<class _T>
concept sparse = container<_T> && callable_contain<_T>;

NGS_MATH_LA_VECTOR_CONCEPT_END