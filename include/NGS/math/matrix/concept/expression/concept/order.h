#pragma once

#include "./expression.h"
#include "../functor/order.h"

NGS_MATH_MATRIX_FUNCTOR_BEGIN

template<class _Left, class _Right>
concept same_type =
expression<_Left> && expression<_Right> &&
functor::valid_row_column<_Left> && functor::valid_row_column<_Right> &&
functor::rows<_Left> == functor::rows<_Right> &&
functor::columns<_Left> == functor::columns<_Right>;

NGS_MATH_MATRIX_FUNCTOR_END