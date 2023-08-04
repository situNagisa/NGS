#pragma once

#include "NGS/math/linear_algebra/base/concepts.h"
#include "NGS/math/linear_algebra/matrix/expression.h"

NGS_MATH_LINEAR_ALGEBRA_BEGIN



template<class T>
concept CMLAMatrixExpression = CMLAExpression<T> && requires() {
	typename T::element_type;
	typename T::functor_type;
};

NGS_MATH_LINEAR_ALGEBRA_END
