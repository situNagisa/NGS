#pragma once

#include "../functor/access.h"
#include "../functor/order.h"

NGS_MATH_MATRIX_FUNCTOR_BEGIN

template<class _T, class _O = type_traits::object_t<_T>>
concept expression = yap::CExpression<_T> && valid_row_column<_O> && accessible<_O>;

NGS_MATH_MATRIX_FUNCTOR_END