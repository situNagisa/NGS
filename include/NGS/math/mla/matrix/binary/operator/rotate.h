#pragma once

#include "NGS/math/mla/matrix/expression/concept.h"
#include "NGS/math/mla/matrix/expression/homogen.h"
#include "NGS/math/mla/scalar/expression/concept.h"
NGS_MLA_BEGIN

template<CMatrixLayout _Layout = tag::row, CScalarExpression _ScalarExpression>
constexpr auto rotate(_ScalarExpression angle) {
	return HomogeneousMatrix<3, _ScalarExpression, tag::row, _Layout>(
		std::cos(angle), -std::sin(angle), 0,
		std::sin(angle), std::cos(angle), 0
	);
}

NGS_MLA_END
