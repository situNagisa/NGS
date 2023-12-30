#pragma once

#include "../tag.h"
#include "./input_or_output.h"

NGS_LIB_MODULE_BEGIN

template<class _M>
concept tag_matrix = input_or_output_matrix<_M> && ::std::derived_from<tag_trait_t<_M>, matrix_tag>;

NGS_LIB_MODULE_END