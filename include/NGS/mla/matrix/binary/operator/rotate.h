#pragma once

#include "NGS/mla/matrix/expression/concept.h"
#include "NGS/mla/matrix/expression/homogen.h"
#include "NGS/mla/scalar/expression/concept.h"
NGS_MLA_BEGIN

template<CHomogeneousMatrix _Container, CScalarExpression _ScalarExpression>
	requires (_Container::dimension == 2)
_Container& rotate_assign(_Container& container, _ScalarExpression angle) {
	if constexpr (is_row_major<typename _Container::homogen_category>) {

	}
	else if constexpr (is_col_major<typename _Container::homogen_category>) {

	}
}

NGS_MLA_END
