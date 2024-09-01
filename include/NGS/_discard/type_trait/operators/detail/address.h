#pragma once

#include "./gen_begin.h"

NGS_TYPE_TRAITS_OPERATORS_BEGIN

//namespace address{
_GEN_OPERATOR_UNARY(is_,dereferencable	,, dereference	, *);
_GEN_OPERATOR_UNARY(is_,addressable		,, address_of	, &);
//}

NGS_TYPE_TRAITS_OPERATORS_END

#include "./gen_end.h"