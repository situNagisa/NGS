#pragma once

#include "./expression.h"

NGS_MATH_LA_VECTOR_CONCEPT_BEGIN

using adapters::vectors::assignable;
using adapters::vectors::callable_contain;

template<class _T, class _O = type_traits::object_t<_T>>
concept container = expression<_T> && assignable<_O, traits::vectors::value_t<_O>>;

template <class _T>
concept output_wrapper = container<_T> && assignable<_T, traits::vectors::value_t<_T>>;

template<class _T>
concept sparse = container<_T> && callable_contain<_T>;

NGS_MATH_LA_VECTOR_CONCEPT_END