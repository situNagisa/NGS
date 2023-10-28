#pragma once

#include "./gen_begin.h"

NGS_TYPE_TRAITS_OPERATORS_BEGIN

//namespace assign{

_GEN_OPERATOR_BINARY(is_,add		,_assignable,add_assign			, +=);
_GEN_OPERATOR_BINARY(is_,subtract	,_assignable,subtract_assign	, -=);
_GEN_OPERATOR_BINARY(is_,multiply	,_assignable,multiply_assign	, *=);
_GEN_OPERATOR_BINARY(is_,divie		,_assignable,divide_assign		, /=);
_GEN_OPERATOR_BINARY(is_,and		,_assignable,and_assign			, &=);
_GEN_OPERATOR_BINARY(is_,or			,_assignable,or_assign			, |=);
_GEN_OPERATOR_BINARY(is_,right_move	,_assignable,right_move_assign	, >>=);
_GEN_OPERATOR_BINARY(is_,left_move	,_assignable,left_move_assign	, <<=);

//}

NGS_TYPE_TRAITS_OPERATORS_END

#include "./gen_end.h"