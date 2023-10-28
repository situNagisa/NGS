#pragma once

#include "../functor.h"
#include "../../expression.h"

NGS_MATH_MATRIX_FUNCTOR_BEGIN

template<class _T, class _O = type_traits::object_t<_T>>
concept container = expression<_T> && assignable<_T, _T>&& assignable<value_t<_T>, _T>&& copyable<_T, _T>;

template<class _T, class _N = type_traits::naked_t<_T>>
concept storage = expression<_T> && assignable<_N, _N>&& assignable<value_t<_N>, _N>&& copyable<_N, _N>;

NGS_MATH_MATRIX_FUNCTOR_END