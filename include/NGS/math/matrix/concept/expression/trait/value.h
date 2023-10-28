#pragma once

#include "../functor/access.h"

NGS_MATH_MATRIX_FUNCTOR_BEGIN

template<class _Type>
using value_t = type_traits::object_t<decltype(access(declval<_Type>(), declval<size_t>(), declval<size_t>()))>;

NGS_MATH_MATRIX_FUNCTOR_END