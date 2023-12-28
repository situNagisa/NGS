#pragma once

#include "./input.h"

NGS_LIB_MODULE_BEGIN

template<class _M>
concept contiguous_matrix = input_matrix<_M> && ::std::ranges::contiguous_range<_M> && vectors::contiguous_vector<::std::ranges::range_value_t<_M>>;

NGS_LIB_MODULE_END