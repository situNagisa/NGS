#pragma once

#include "../dimension.h"
#include "./expression.h"

NGS_MATH_VECTOR_FUNCTOR_BEGIN

template<class _T, size_t _Dimension, class _O = type_traits::object_t<_T>>
concept dimension_is = expression<_T> && valid_dimension<_O> && (dimension<_O> == _Dimension);

template<class _Left, class _Right, class _L = type_traits::object_t<_Left>, class _R = type_traits::object_t<_Right>>
concept dimension_equality = expression<_Left> && expression<_Right> && valid_dimension<_L> && valid_dimension<_R> && (dimension<_L> == dimension<_R>);

NGS_MATH_VECTOR_FUNCTOR_END