#pragma once

#include "./input_or_output.h"

NGS_LIB_BEGIN

struct vector_tag {};

NGS_LIB_END
NGS_LIB_MODULE_BEGIN

template<class _V>
concept tag_vector = input_or_output_vector<_V> && ::std::derived_from<typename type_traits::object_t<_V>::nmla_type, vector_tag>;

NGS_LIB_MODULE_END