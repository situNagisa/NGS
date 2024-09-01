#pragma once

#include "./depth.h"
#include "./tag.h"
#include "./defined.h"

NGS_LIB_BEGIN

template<class _T>
inline constexpr bool enable_operator_vector = false;

NGS_LIB_END
NGS_LIB_MODULE_BEGIN

template<class _T>
concept operator_vector = pure_vector<_T> && ((tag_vector<_T> && scalar_vector<_T>) || enable_operator_vector<_T>);

NGS_MATH_VECTOR_RECURSE_ANCHOR_CONCEPT_UNARY(operator_vector);

NGS_LIB_MODULE_END