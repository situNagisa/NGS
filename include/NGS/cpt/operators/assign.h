#pragma once

#include "./gen_begin.h"

NGS_CPT_BEGIN

//namespace assign{

_GEN_OPERATOR_BINARY(add_assignable			, is_add_assignable);
_GEN_OPERATOR_BINARY(subtract_assignable	, is_subtract_assignable);
_GEN_OPERATOR_BINARY(multiply_assignable	, is_multiply_assignable);
_GEN_OPERATOR_BINARY(divide_assignable		, is_divie_assignable);
_GEN_OPERATOR_BINARY(and_assignable			, is_and_assignable);
_GEN_OPERATOR_BINARY(or_assignable			, is_or_assignable);
_GEN_OPERATOR_BINARY(right_move_assignale	, is_right_move_assignable);
_GEN_OPERATOR_BINARY(left_move_assignable	, is_left_move_assignable);

//}

NGS_CPT_END

#include "./gen_end.h"