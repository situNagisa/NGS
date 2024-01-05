#pragma once

#include "../value.h"
#include "./depth.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

template<class _M>
concept input_or_output_matrix = generalized_matrix<_M> && vectors::input_or_output_vector<_M> && vectors::input_or_output_vector_at<_M, 1>;

template<class _M>
concept input_matrix = input_or_output_matrix<_M> && vectors::input_vector<_M> && vectors::input_vector_at<_M, 1>;

template<class _M, class _E = ::std::conditional_t<input_or_output_matrix<_M>, matrix_value_t<_M>, void>>
concept output_matrix = input_or_output_matrix<_M> && vectors::output_vector<::std::ranges::range_value_t<_M>, _E>;

NGS_LIB_MODULE_END