#pragma once

#include "NGS/math/vector/concept.h"
#include "./iterator.h"

NGS_MATH_VECTOR_BEGIN

template<functor::accessible _Type>
struct iterator
{
	using input = detail::vector_expression_iterator<const _Type>;
	using reverse_input = detail::vector_expression_iterator<const _Type>;
};
template<functor::accessible _Type>
	requires functor::assignable<functor::value_t<_Type>, _Type>
struct iterator<_Type>
{
	using input = detail::vector_expression_iterator<const _Type>;
	using reverse_input = detail::vector_expression_iterator<const _Type>;

	using input_or_output = detail::vector_expression_iterator<_Type>;
	using reverse_input_or_output = detail::vector_expression_iterator<_Type>;
};

template<functor::accessible _Type>
using in_iterator_t = typename iterator<_Type>::input;
template<functor::accessible _Type>
using reverse_in_iterator_t = typename iterator<_Type>::reverse_input;
template<functor::accessible _Type>
	requires functor::assignable<functor::value_t<_Type>, _Type>
using io_iterator_t = typename iterator<_Type>::input_or_output;
template<functor::accessible _Type>
	requires functor::assignable<functor::value_t<_Type>, _Type>
using reverse_io_iterator_t = typename iterator<_Type>::reverse_input_or_output;

NGS_MATH_VECTOR_END