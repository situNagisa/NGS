#pragma once

#include "../functor.h"

NGS_MATH_VECTOR_FUNCTOR_BEGIN

/**
 * @brief vector expression concept
 *
 * @tparam _T
*/
template<class _T, class _O = type_traits::object_t<_T>>
concept expression = yap::CExpression<_T> && valid_dimension<_O> && accessible<_O>;

NGS_MATH_VECTOR_FUNCTOR_END