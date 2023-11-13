#pragma once

#include "../defined.h"

NGS_MATH_LA_VECTOR_CONCEPT_BEGIN

template<class _Left, class _Right>
concept arithmetic_operatable_with = expression<_Left> && expression<_Right> && same_type<_Left, _Right>;

NGS_MATH_LA_VECTOR_CONCEPT_END