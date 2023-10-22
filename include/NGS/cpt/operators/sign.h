#pragma once

#include "./gen_begin.h"

NGS_CPT_BEGIN

//namespace sign{

_GEN_OPERATOR_UNARY(positivable, is_positivable);
_GEN_OPERATOR_UNARY(negativable, is_negativable);

template<class _Type>
concept sign_operable = positivable<_Type> && negativable<_Type>;

//}

NGS_CPT_END

#include "./gen_end.h"