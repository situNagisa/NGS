#pragma once

#include "NGS/math/linear_algebra/base/concepts.h"
#include "NGS/math/linear_algebra/matrix/expression.h"

NGS_MATH_LINEAR_ALGEBRA_BEGIN

template<class T>
concept CMLAMatrix = requires(T matrix, const T matrix_cst) {
	typename T::element_type;
	{ matrix(0, 0) } -> std::convertible_to<typename T::element_type>;

	{ matrix_cst.row_size() } -> std::convertible_to<size_t>;

	{ matrix_cst.col_size() } -> std::convertible_to<size_t>;
};

template<class T>
concept CMLAMatrixExpression = CMLAExpression<T> && requires() {
	typename T::element_type;
	typename T::functor_type;
};

NGS_MATH_LINEAR_ALGEBRA_END
