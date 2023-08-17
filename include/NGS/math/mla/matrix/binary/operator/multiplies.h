#pragma once

#include "NGS/math/mla/matrix/binary/binary.h"
#include "NGS/math/mla/scalar/binary.h"
#include "NGS/math/mla/matrix/expression/container.h"
#include "NGS/math/mla/matrix/expression/scalar.h"
#include "NGS/math/mla/vector/binary.h"
#include "NGS/math/mla/vector/expression/concept.h"
#include "NGS/math/mla/matrix/unary/operator/access.h"
#include "NGS/math/mla/matrix/expression/vector.h"
#include "NGS/math/mla/scalar/expression/concept.h"
#include "NGS/math/mla/vector/unary/operator/homogen.h"

NGS_MLA_BEGIN

//=====================
// quantity
//=====================

template<CMatrixExpression _Expression, CScalarExpression _ScalarExpression>
constexpr auto multiplies_scalar(const _Expression& expression, _ScalarExpression scalar) {
	using scalar_t = matrix_scalar_expression_t<matrix_traits<_Expression>::row_count, matrix_traits<_Expression>::col_count, _ScalarExpression>;
	using binary_t = matrix_binary_scalar_t<_Expression, scalar_t, ScalarMultipliesFunctor>;
	return binary_t(expression, scalar_t(scalar));
}

template<CMatrixExpression _Expression, CScalarExpression _ScalarExpression>
constexpr auto multiplies_scalar(_ScalarExpression scalar, const _Expression& expression) {
	using scalar_t = matrix_scalar_expression_t<matrix_traits<_Expression>::row_count, matrix_traits<_Expression>::col_count, _ScalarExpression>;
	using binary_t = matrix_binary_scalar_t<scalar_t, _Expression, ScalarMultipliesFunctor>;
	return binary_t(scalar_t(scalar), expression);
}
template<CMatrixExpression _Expression, CScalarExpression _ScalarExpression>
constexpr auto operator*(_ScalarExpression scalar, const _Expression& expression) { return multiplies_scalar(scalar, expression); }
template<CMatrixExpression _Expression, CScalarExpression _ScalarExpression>
constexpr auto operator*(const _Expression& expression, _ScalarExpression scalar) { return multiplies_scalar(expression, scalar); }

template<CMatrixContainer _Container, CScalarExpression _ScalarExpression>
_Container& multiplies_assign(_Container& container, _ScalarExpression scalar) { return container.assign(multiplies_scalar(container, scalar)); }
template<CMatrixContainer _Container, CScalarExpression _ScalarExpression>
_Container& operator*=(_Container& container, _ScalarExpression scalar) { return multiplies_assign(container, scalar); }

//=====================
// matrix multiplies
//=====================

template<CMatrixExpression _Left, CMatrixExpression _Right>
struct NGS_API MatrixMultipliesFunctor {
private:
	using left_t = typename matrix_traits<_Left>::original_type;
	using right_t = typename matrix_traits<_Right>::original_type;
	using result_type = mpl::promote_t<typename matrix_traits<_Left>::element_type, typename matrix_traits<_Right>::element_type>;
public:

	constexpr static result_type apply(const left_t& left, const right_t& right, size_t row_index, size_t col_index) {
		return product_inner(row(left(), row_index), column(right(), col_index));
	}
};

template<CMatrixExpression _Left, CMatrixExpression _Right> requires (matrix_traits<_Left>::col_count == matrix_traits<_Right>::row_count)
constexpr auto multiplies(const _Left& left, const _Right& right) {
	using binary_t = matrix_binary_t<_Left, _Right, MatrixMultipliesFunctor<_Left, _Right>>;
	return binary_t(left, right);
}

template<CMatrixExpression _Left, CMatrixExpression _Right> requires (matrix_traits<_Left>::col_count == matrix_traits<_Right>::row_count)
constexpr auto operator*(const _Left& left, const _Right& right) { return multiplies(left, right); }

template<CMatrixContainer _Container, CMatrixExpression _Right> requires (matrix_traits<_Container>::col_count == matrix_traits<_Right>::row_count)
_Container& multiplies_assign(_Container& container, const _Right& right) { return container.assign(multiplies(container, right)); }
template<CMatrixContainer _Container, CMatrixExpression _Right> requires (matrix_traits<_Container>::col_count == matrix_traits<_Right>::row_count)
_Container& operator*=(_Container& container, const _Right& right) { return multiplies_assign(container, right); }


//=====================
// vector
//=====================
template<CMatrixExpression _Matrix, CVectorExpression _Vector>
	requires (matrix_traits<_Matrix>::col_count == vector_traits<_Vector>::dimension)
constexpr auto multiplies_vector(const _Matrix& matrix, const _Vector& vector) {
	using vector_t = MatrixVectorExpression<_Vector, tag::column>;
	return multiplies(matrix, vector_t(vector));
}
template<CMatrixExpression _Matrix, CVectorExpression _Vector>
	requires (matrix_traits<_Matrix>::row_count == vector_traits<_Vector>::dimension)
constexpr auto multiplies_vector(const _Vector& vector, const _Matrix& matrix) {
	using vector_t = MatrixVectorExpression<_Vector, tag::row>;
	return multiplies(vector_t(vector), matrix);
}
template<CMatrixExpression _Matrix, CVectorExpression _Vector>
	requires (matrix_traits<_Matrix>::col_count == vector_traits<_Vector>::dimension + 1)
constexpr auto multiplies_vector(const _Matrix& matrix, const _Vector& vector) {
	using vector_t = VectorHomogenousExpression<_Vector>;
	using matrix_t = MatrixVectorExpression<vector_t, tag::column>;
	return multiplies(matrix, matrix_t(vector_t(vector)));
}
template<CMatrixExpression _Matrix, CVectorExpression _Vector>
	requires (matrix_traits<_Matrix>::row_count == vector_traits<_Vector>::dimension + 1)
constexpr auto multiplies_vector(const _Vector& vector, const _Matrix& matrix) {
	using vector_t = VectorHomogenousExpression<_Vector>;
	using matrix_t = MatrixVectorExpression<vector_t, tag::row>;
	return multiplies(matrix_t(vector_t(vector)), matrix);
}

template<CMatrixContainer _Container, CVectorExpression _Vector>
	requires (matrix_traits<_Container>::col_count == vector_traits<_Vector>::dimension) || (matrix_traits<_Container>::col_count == vector_traits<_Vector>::dimension + 1)
_Container & multiplies_assign(_Container & container, const _Vector & vector) { return container.assign(multiplies_vector(container, vector)); }

template<CMatrixExpression _Matrix, CVectorExpression _Vector>
	requires (matrix_traits<_Matrix>::col_count == vector_traits<_Vector>::dimension) || (matrix_traits<_Matrix>::col_count == vector_traits<_Vector>::dimension + 1)
constexpr auto operator*(const _Matrix & matrix, const _Vector & vector) { return multiplies_vector(matrix, vector); }
template<CMatrixExpression _Matrix, CVectorExpression _Vector>
	requires (matrix_traits<_Matrix>::row_count == vector_traits<_Vector>::dimension) || (matrix_traits<_Matrix>::row_count == vector_traits<_Vector>::dimension + 1)
constexpr auto operator*(const _Vector & vector, const _Matrix & matrix) { return multiplies_vector(vector, matrix); }
template<CMatrixContainer _Container, CVectorExpression _Vector>
	requires (matrix_traits<_Container>::col_count == vector_traits<_Vector>::dimension) || (matrix_traits<_Container>::col_count == vector_traits<_Vector>::dimension + 1)
_Container & operator*=(_Container & container, const _Vector & vector) { return multiplies_assign(container, vector); }


NGS_MLA_END
