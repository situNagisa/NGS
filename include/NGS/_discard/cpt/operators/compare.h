#pragma once

#include "./gen_begin.h"

NGS_CPT_BEGIN

//namespace compare{

_GEN_OPERATOR_BINARY(greater_comparable			, is_greater_comparable);
_GEN_OPERATOR_BINARY(less_comparable			, is_less_comparable);
//_GEN_OPERATOR_BINARY(equal_comparable			, is_equal_comparable);
_GEN_OPERATOR_BINARY(greater_equal_comparable	, is_greater_equal_comparable);
_GEN_OPERATOR_BINARY(less_equal_comparable		, is_less_equal_comparable);
//_GEN_OPERATOR_BINARY(three_way_comparable		, is_three_way_comparable);

//}

NGS_CPT_END

#include "./gen_end.h"