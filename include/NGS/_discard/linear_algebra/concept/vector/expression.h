#pragma once

#include "./defined.h"

NGS_MATH_LA_VECTOR_CONCEPT_BEGIN

using adapters::vectors::valid_dimension;
using adapters::vectors::invalid_dimension;
using adapters::vectors::dynamic_dimension;
using adapters::vectors::dimension_equality;
using adapters::vectors::same_type;
using adapters::vectors::accessible;

template<class _T>
concept expression = yap::CExpression<_T> && valid_dimension<_T> && accessible<_T>;

NGS_MATH_LA_VECTOR_CONCEPT_END