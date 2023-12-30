#pragma once

#include "./defined.h"

NGS_LIB_MODULE_BEGIN

template<class _M>
concept input_or_output_matrix = vectors::input_or_output_vector<_M> && vectors::input_or_output_vector<::std::ranges::range_value_t<_M>>;

NGS_LIB_MODULE_END
