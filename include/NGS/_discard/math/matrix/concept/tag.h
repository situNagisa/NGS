#pragma once

#include "../tag.h"
#include "./depth.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

template<class _M, class _Tag = NGS_MATH_MATRIX_TAG_NS::matrix>
concept tag_matrix = generalized_matrix<_M> && ::std::derived_from<NGS_MATH_MATRIX_TAG_NS::trait_t<_M>, _Tag>;

NGS_LIB_MODULE_END