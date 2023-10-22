#pragma once

#include "./gen_begin.h"

NGS_TYPE_TRAITS_OPERATORS_BEGIN

//namespace bit{

_GEN_OPERATOR_UNARY( is_,notable		,,not		, ~);
_GEN_OPERATOR_BINARY(is_,andable		,,and		, &);
_GEN_OPERATOR_BINARY(is_,orable			,,or		, | );
_GEN_OPERATOR_BINARY(is_,right_movable	,,right_move, >> );
_GEN_OPERATOR_BINARY(is_,left_movable	,,left_move	, << );

//}

NGS_TYPE_TRAITS_OPERATORS_END

#include "./gen_end.h"