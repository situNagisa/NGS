#pragma once

#include "NGS/math/mla/matrix/expression/concept.h"
#include "NGS/math/mla/matrix/traits.h"
#include "NGS/math/mla/vector/expression/concept.h"
#include "NGS/math/mla/vector/traits.h"

#include "NGS/math/mla/matrix/expression/homogen.h"
#include "NGS/math/mla/vector/unary/operator/homogen.h"
#include "NGS/math/mla/matrix/expression/identity.h"

NGS_MLA_BEGIN

template<CHomogeneousMatrix _Matrix, CVectorExpression _Vector>
	requires (_Matrix::dimension == vector_traits<_Vector>::dimension)
struct MatrixScale : MatrixExpression<MatrixScale<_Matrix, _Vector>> {
private:
	using base_type = MatrixScale::self_type;
protected:
	using self_type = MatrixScale;
private:
	using matrix_closure_type = typename matrix_traits<_Matrix>::closure_type;
	using vector_closure_type = typename vector_traits<_Vector>::closure_type;
public:
	constexpr static size_t complexity = matrix_traits<_Matrix>::complexity + vector_traits<_Vector>::complexity + 1;
	constexpr static size_t row_count = matrix_traits<_Matrix>::row_count;
	constexpr static size_t col_count = matrix_traits<_Matrix>::col_count;
	constexpr static size_t element_count = row_count * col_count;
	constexpr static size_t dimension = _Matrix::dimension;

	using element_type = typename matrix_traits<_Matrix>::element_type;
	using homogen_category = typename _Matrix::homogen_category;

	constexpr explicit MatrixScale(matrix_closure_type matrix, vector_closure_type vector) :
		_matrix(matrix),
		_vector(vector)
	{}

	using base_type::operator();
	constexpr element_type operator()(size_t row_index, size_t col_index)const {
		if constexpr (is_row_major<homogen_category>) {
			[[likely]]
			if (row_index != (row_count - 1))
				return _matrix()(row_index, col_index) * _vector()(row_index);
			else
				return _matrix()(row_index, col_index);
		}
		else if constexpr (is_col_major<homogen_category>) {
			[[likely]]
			if (col_index != (col_count - 1))
				return _matrix()(row_index, col_index) * _vector()(col_index);
			else
				return _matrix()(row_index, col_index);
		}
	}

private:
	matrix_closure_type _matrix;
	vector_closure_type _vector;
};

template<CHomogeneousMatrix _Matrix, CVectorExpression _Vector> requires (_Matrix::dimension - 1 == vector_traits<_Vector>::dimension)
constexpr auto scale(const _Matrix& matrix, const _Vector& vector) {
	using vector_t = VectorHomogenousExpression<_Vector>;
	return MatrixScale<_Matrix, vector_t>(matrix, vector_t(vector));
}
template<CHomogeneousMatrix _Matrix, CVectorExpression _Vector> requires (_Matrix::dimension - 1 == vector_traits<_Vector>::dimension)
constexpr auto scale(const _Vector& vector, const _Matrix& matrix) {
	using vector_t = VectorHomogenousExpression<_Vector>;
	return MatrixScale<_Matrix, vector_t>(matrix, vector_t(vector));
}
template<CMatrixLayout _Layout = tag::row, CVectorExpression _Vector>
constexpr auto scale(const _Vector& vector) {
	using matrix_t = HomogeneousMatrix<_Vector::dimension + 1, typename _Vector::element_type, tag::row, _Layout>;
	return scale(matrix_t(identity_matrix_v<matrix_t::dimension, typename matrix_t::element_type>), vector);
}
template<CHomogeneousMatrix _Container, CVectorExpression _Vector> requires (_Container::dimension - 1 == vector_traits<_Vector>::dimension) && CMatrixContainer<_Container>
_Container& scale_assign(_Container& container, const _Vector& vector) {
	if constexpr (is_row_major<typename _Container::homogen_category>) {
		for (size_t row_index = 0; row_index < _Container::dimension - 1; row_index++)
		{
			for (size_t col_index = 0; col_index < _Container::dimension; col_index++)
			{
				container().assign(row_index, col_index, container()(row_index, col_index) * vector()(row_index));
			}
		}
	}
	else if constexpr (is_col_major<typename _Container::homogen_category>) {
		for (size_t row_index = 0; row_index < _Container::dimension; row_index++)
		{
			for (size_t col_index = 0; col_index < _Container::dimension - 1; col_index++)
			{
				container().assign(row_index, col_index, container()(row_index, col_index) * vector()(col_index));
			}
		}
	}
	return container;
}


//template<CHomogeneousMatrix _Matrix, CVectorExpression _Vector> requires (_Matrix::dimension - 1 == vector_traits<_Vector>::dimension)
//constexpr auto operator*(const _Matrix& matrix, const _Vector& vector) { return scale(matrix, vector); }
//template<CHomogeneousMatrix _Matrix, CVectorExpression _Vector> requires (_Matrix::dimension - 1 == vector_traits<_Vector>::dimension)
//constexpr auto operator*(const _Vector& vector, const _Matrix& matrix) { return scale(vector, matrix); }
//template<CHomogeneousMatrix _Container, CVectorExpression _Vector> requires (_Container::dimension - 1 == vector_traits<_Vector>::dimension) && CMatrixContainer<_Container>
//_Container& operator*=(const _Container& container, const _Vector& vector) { return scale_assign(container, vector); }

NGS_MLA_END
