#pragma once

#include "./defined.h"

NGS_MATH_SCALAR_CONCEPTS_BEGIN

template<class _T,class _O = type_traits::object_t<_T>>
concept scalar = true;

NGS_MATH_SCALAR_CONCEPTS_END