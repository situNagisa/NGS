#pragma once

#include "NGS/mla/matrix/expression/concept.h"
#include "NGS/mla/matrix/traits.h"
#include "NGS/mla/vector/expression/concept.h"
#include "NGS/mla/vector/traits.h"

#include "NGS/mla/matrix/expression/homogen.h"

NGS_MLA_BEGIN

template<CHomogeneousMatrix _Matrix, CVectorExpression _Vector>
	requires (_Matrix::dimension - 1 == vector_traits<_Vector>::dimension)
struct MatrixTranslate : MatrixExpression<MatrixTranslate<_Matrix, _Vector>> {
private:
	using base_type = MatrixTranslate::self_type;
protected:
	using self_type = MatrixTranslate;
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

	constexpr explicit MatrixTranslate(matrix_closure_type matrix, vector_closure_type vector) :
		_matrix(matrix),
		_vector(vector)
	{}

	using base_type::operator();
	constexpr element_type operator()(size_t row_index, size_t col_index)const {
		if constexpr (is_row_major<homogen_category>) {
			[[unlikely]]
			if (col_index == (col_count - 1))
				return _matrix()(row_index, col_index) + _vector()(row_index);
			else
				return _matrix()(row_index, col_index);
		}
		else if constexpr (is_col_major<homogen_category>) {
			[[unlikely]]
			if (row_index == (row_count - 1))
				return _matrix()(row_index, col_index) + _vector()(col_index);
			else
				return _matrix()(row_index, col_index);
		}
	}

private:
	matrix_closure_type _matrix;
	vector_closure_type _vector;
};

template<CHomogeneousMatrix _Matrix, CVectorExpression _Vector> requires (_Matrix::dimension - 1 == vector_traits<_Vector>::dimension)
constexpr auto translate(const _Matrix& matrix, const _Vector& vector) { return MatrixTranslate<_Matrix, _Vector>(matrix, vector); }
template<CVectorExpression _Vector, CHomogeneousMatrix _Matrix> requires (_Matrix::dimension - 1 == vector_traits<_Vector>::dimension)
constexpr auto translate(const _Vector& vector, const _Matrix& matrix) { return MatrixTranslate<_Matrix, _Vector>(matrix, vector); }
template<CHomogeneousMatrix _Container, CVectorExpression _Vector> requires CMatrixContainer<_Container> && (_Container::dimension - 1 == vector_traits<_Vector>::dimension)
constexpr _Container& translate_assign(_Container& container, const _Vector& vector) {
	if constexpr (is_row_major<typename _Container::homogen_category>) {
		for (size_t i = 0; i < vector_traits<_Vector>::dimension; i++)
		{
			container().assign(i, _Container::col_count - 1, container()(i, _Container::col_count - 1) + vector()(i));
		}
	}
	else if constexpr (is_col_major<typename _Container::homogen_category>) {
		for (size_t i = 0; i < vector_traits<_Vector>::dimension; i++)
		{
			container().assign(_Container::row_count - 1, i, container()(_Container::row_count - 1, i) + vector()(i));
		}
	}
	return container;
}

template<CHomogeneousMatrix _Matrix, CVectorExpression _Vector> requires (_Matrix::dimension - 1 == vector_traits<_Vector>::dimension)
constexpr auto operator+(const _Matrix& matrix, const _Vector& vector) { return translate(matrix, vector); }
template<CVectorExpression _Vector, CHomogeneousMatrix _Matrix> requires (_Matrix::dimension - 1 == vector_traits<_Vector>::dimension)
constexpr auto operator+(const _Vector& vector, const _Matrix& matrix) { return translate(vector, matrix); }
template<CHomogeneousMatrix _Container, CVectorExpression _Vector> requires CMatrixContainer<_Container> && (_Container::dimension - 1 == vector_traits<_Vector>::dimension)
constexpr _Container& operator+=(_Container& container, const _Vector& vector) { return translate_assign(container, vector); }

NGS_MLA_END
