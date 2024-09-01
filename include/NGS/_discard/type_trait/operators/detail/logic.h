#pragma once

#include "./gen_begin.h"

NGS_TYPE_TRAITS_OPERATORS_BEGIN

//namespace logic{

_GEN_OPERATOR_UNARY( is_logic_,notable	,,logic_not	, !);
_GEN_OPERATOR_BINARY(is_logic_,andable	,,logic_and	, &&);
_GEN_OPERATOR_BINARY(is_logic_,orable	,,logic_or	, || );

//}

NGS_TYPE_TRAITS_OPERATORS_END

#include "./gen_end.h"