#pragma once

#include "./gen_begin.h"

NGS_CPT_BEGIN

//namespace bit{

_GEN_OPERATOR_UNARY (notable		, is_notable);
_GEN_OPERATOR_BINARY(andable		, is_andable);
_GEN_OPERATOR_BINARY(orable			, is_orable);
_GEN_OPERATOR_BINARY(right_movable	, is_right_movable);
_GEN_OPERATOR_BINARY(left_movable	, is_left_movable);

template<class _Left, class _Right = _Left>
concept bit_operable = andable<_Left, _Right> && orable<_Left, _Right> && right_movable<_Left, _Right> && left_movable<_Left, _Right>;

//}

NGS_CPT_END

#include "./gen_end.h"