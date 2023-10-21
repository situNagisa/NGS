#pragma once

#include "../assign.h"
#include "../copy.h"
#include "../../expression.h"

NGS_MATH_VECTOR_FUNCTOR_BEGIN

template<class _T,class _O = type_traits::object_t<_T>>
concept container = expression<_T> && assignable<_T, _T> && assignable<vector_value_t<_T>,_T> && copyable<_T, _T>;

NGS_MATH_VECTOR_FUNCTOR_END