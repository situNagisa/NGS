#pragma once

#include "../operator.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

template<vectors::scalar _Value, vectors::extent_t _Dimension>
using internals = bases::adl_forward<vectors::vector<internal<_Value>, _Dimension>, NGS_MATH_BOX_OPERATOR_NS::allow_adl_operator>;

NGS_LIB_MODULE_END