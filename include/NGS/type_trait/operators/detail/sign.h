#pragma once

#include "./gen_begin.h"

NGS_TYPE_TRAITS_OPERATORS_BEGIN

//namespace sign{

_GEN_OPERATOR_UNARY(is_,positivable,,positive, +);
_GEN_OPERATOR_UNARY(is_,negativable,,negative, -);

//}

NGS_TYPE_TRAITS_OPERATORS_END

#include "./gen_end.h"