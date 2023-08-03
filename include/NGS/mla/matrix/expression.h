#pragma once

#include "NGS/math/linear_algebra/base/expression.h"
#include "NGS/math/linear_algebra/matrix/tag.h"

NGS_MATH_LINEAR_ALGEBRA_BEGIN

template<class _Expression>
struct MatrixExpression : Expression<_Expression> {
private:
	using base_type = MatrixExpression::self_type;
protected:
	using self_type = MatrixExpression<_Expression>;
public:
	using type_category = tag::matrix;
};

NGS_MATH_LINEAR_ALGEBRA_END
