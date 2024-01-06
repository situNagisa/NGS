#pragma once

#include "./depth.h"
#include "../tag.h"

NGS_LIB_MODULE_BEGIN

template<class _V, class _Tag = NGS_MATH_VECTOR_TAG_NS::vector>
concept tag_vector = generalized_vector<_V> && ::std::derived_from<NGS_MATH_VECTOR_TAG_NS::trait_t<_V>, _Tag >;

NGS_MATH_VECTOR_RECURSE_ANCHOR_CONCEPT_UNARY(tag_vector);

NGS_LIB_MODULE_END