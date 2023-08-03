#pragma once

#include "NGS/math/linear_algebra/matrix/expression.h"

NGS_MATH_LINEAR_ALGEBRA_BEGIN

template<class _Container>
class MatrixContainer : public MatrixExpression<_Container>
{

public:
	using container_type = _Container;
};
static_assert(CMLAContainer<MatrixContainer<int>>);

NGS_MATH_LINEAR_ALGEBRA_END
