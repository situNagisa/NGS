#pragma once

#include "./gen_begin.h"

NGS_TYPE_TRAITS_OPERATORS_BEGIN

//namespace compare{

_GEN_OPERATOR_BINARY(is_,greater		,_comparable,greater		, > );
_GEN_OPERATOR_BINARY(is_,less			,_comparable,less			, < );
//_GEN_OPERATOR_BINARY(is_,equal			,_comparable,equal			, == );
_GEN_OPERATOR_BINARY(is_,greater_equal	,_comparable,greater_equal	, >= );
_GEN_OPERATOR_BINARY(is_,less_equal		,_comparable,less_equal		, <= );
//_GEN_OPERATOR_BINARY(is_,three_way		,_comparable,three_way		, <=> );

//}

NGS_TYPE_TRAITS_OPERATORS_END

#include "./gen_end.h"