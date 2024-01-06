#pragma once

#include "./depth.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

template<class _M>
concept block_matrix = generalized_matrix<_M>

NGS_LIB_MODULE_END
