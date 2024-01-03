#pragma once

#include "./scalar.h"
#include "./tag.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

template<class _M>
concept operator_matrix = scalar_matrix<_M> && tag_matrix<_M>;

NGS_LIB_MODULE_END