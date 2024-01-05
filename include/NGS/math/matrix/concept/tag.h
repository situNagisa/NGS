#pragma once

#include "../tag.h"
#include "./depth.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

template<class _M>
concept tag_matrix = generalized_matrix<_M> && vectors::tag_vector<_M> && vectors::tag_vector_at<_M, 1>;

NGS_LIB_MODULE_END