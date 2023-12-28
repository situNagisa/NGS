#pragma once

#include "./expression.h"

NGS_MATH_VECTOR_FUNCTOR_BEGIN

template<class _T, class _O = type_traits::object_t<_T>>
concept standard_size = sizeof(_O) == (sizeof(value_t<_T>) * dimension<_T>);

NGS_MATH_VECTOR_FUNCTOR_END