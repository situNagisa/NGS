#pragma once

#include "./io.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

template<class _M>
concept random_access_matrix = input_matrix<_M> && vectors::random_access_vector<_M> && vectors::random_access_vector_at<_M, 1>;

template<class _M>
concept contiguous_matrix = random_access_matrix<_M> && vectors::contiguous_vector<_M> && vectors::contiguous_vector_at<_M, 1>;

template<class _V>
concept sized_matrix = input_or_output_matrix<_V> && vectors::sized_vector<_V> && vectors::sized_vector_at<_V, 1>;

NGS_LIB_MODULE_END