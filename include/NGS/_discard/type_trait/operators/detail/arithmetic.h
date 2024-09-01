#pragma once

#include "./gen_begin.h"

NGS_TYPE_TRAITS_OPERATORS_BEGIN

//namespace arithmetic{

_GEN_OPERATOR_UNARY( is_,	auto_incrementable	,,auto_increase	, ++);
_GEN_OPERATOR_UNARY( is_,	auto_decrementable	,,auto_decrease	, --);
_GEN_OPERATOR_BINARY(is_,	addable				,,add			, +);
_GEN_OPERATOR_BINARY(is_,	subtractable		,,subtract		, -);
_GEN_OPERATOR_BINARY(is_,	multipliable		,,multiply		, *);
_GEN_OPERATOR_BINARY(is_,	divisible			,,divide		, / );

//}

NGS_TYPE_TRAITS_OPERATORS_END

#include "./gen_end.h"