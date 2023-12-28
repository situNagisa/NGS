#pragma once

#include "../tag.h"
#include "./input_or_output.h"

NGS_LIB_MODULE_BEGIN

template<class _V>
concept tag_vector = input_or_output_vector<_V> && ::std::derived_from<tag_trait_t<_V>, vector_tag>;

NGS_LIB_MODULE_END