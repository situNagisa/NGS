#pragma once

#include "./gen_begin.h"

NGS_CPT_BEGIN

//namespace logic{

_GEN_OPERATOR_UNARY (logic_notable	, is_logic_notable);
_GEN_OPERATOR_BINARY(logic_andable	, is_logic_andable);
_GEN_OPERATOR_BINARY(logic_orable	, is_logic_orable);

template<class _Left, class _Right = _Left>
concept logic_operable = logic_andable<_Left, _Right> && logic_orable<_Left, _Right>;

//}

NGS_CPT_END

#include "./gen_end.h"