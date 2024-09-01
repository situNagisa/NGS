#pragma once

#include "./gen_begin.h"

NGS_CPT_BEGIN

//namespace arithmetic{

_GEN_OPERATOR_UNARY( auto_incrementable	, is_auto_incrementable);
_GEN_OPERATOR_UNARY( auto_decrementable	, is_auto_decrementable);
_GEN_OPERATOR_BINARY(addable			, is_addable);
_GEN_OPERATOR_BINARY(subtractable		, is_subtractable);
_GEN_OPERATOR_BINARY(multipliable		, is_multipliable);
_GEN_OPERATOR_BINARY(divisible			, is_divisible);

template<class _Left, class _Right = _Left>
concept arithmetic_operable = addable<_Left,_Right> && subtractable<_Left,_Right> && multipliable<_Left,_Right> && divisible<_Left,_Right>;

//}

NGS_CPT_END

#include "./gen_end.h"