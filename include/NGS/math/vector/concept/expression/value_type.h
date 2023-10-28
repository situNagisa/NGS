#pragma once

#include "./access.h"

NGS_MATH_VECTOR_FUNCTOR_BEGIN

template<class _Type>
using value_t = type_traits::object_t<decltype(access(declval<_Type>(), declval<size_t>()))>;

NGS_MATH_VECTOR_FUNCTOR_END