#pragma once

#include "../value.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

template<class _M>
concept generalized_matrix = vectors::generalized_vector<_M> && (vectors::depth_v<_M> >= 2);

template<class _M>
concept pure_matrix = generalized_matrix<_M> && (vectors::depth_v<_M> == 2);

template<class _M>
concept non_matrix = !generalized_matrix<_M>;

using vectors::scalar;

template<class _M>
concept scalar_matrix = pure_matrix<_M> && scalar<matrix_value_t<_M>>;

NGS_LIB_MODULE_END