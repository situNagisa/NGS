#pragma once

#include "NGS/math/mla/matrix/expression/concept.h"
#include "NGS/math/mla/matrix/traits.h"
#include "NGS/math/mla/vector/expression/concept.h"
#include "NGS/math/mla/vector/traits.h"

#include "NGS/math/mla/matrix/expression/homogen.h"
#include "NGS/math/mla/vector/unary/operator/homogen.h"
#include "NGS/math/mla/matrix/expression/identity.h"

NGS_MLA_BEGIN

template<CVectorExpression _Vector, CMatrixLayout _Homo = tag::row>
struct NGS_DLL_API MatrixTranslate : MatrixExpression<MatrixTranslate<_Vector>> {
	NGS_MPL_ENVIRON(MatrixTranslate);
private:
	using vector_closure_type = typename vector_traits<_Vector>::closure_type;
public:
	constexpr static size_t complexity = vector_traits<_Vector>::complexity + 1;
	constexpr static size_t dimension = vector_traits<_Vector>::dimension + 1;
	constexpr static size_t row_count = dimension;
	constexpr static size_t col_count = dimension;
	constexpr static size_t element_count = row_count * col_count;

	using element_type = typename vector_traits<_Vector>::element_type;
	using homogen_category = _Homo;

	constexpr explicit MatrixTranslate(vector_closure_type vector) :
		_vector(vector)
	{}

	using base_type::operator();
	constexpr element_type operator()(size_t row_index, size_t col_index)const {
		if constexpr (is_row_major<homogen_category>) {
			[[unlikely]]
			if (col_index == (col_count - 1))
				return identity_matrix_v<dimension,element_type>(row_index, col_index) + _vector()(row_index);
			else
				return identity_matrix_v<dimension, element_type>(row_index, col_index);
		}
		else if constexpr (is_col_major<homogen_category>) {
			[[unlikely]]
			if (row_index == (row_count - 1))
				return identity_matrix_v<dimension, element_type>(row_index, col_index) + _vector()(col_index);
			else
				return identity_matrix_v<dimension, element_type>(row_index, col_index);
		}
	}

private:
	vector_closure_type _vector;
};

template<CMatrixLayout _Homo = tag::row, CVectorExpression _Vector>
constexpr auto translate(const _Vector& vector) {
	return MatrixTranslate<_Vector, _Homo>(vector);
}

template<CHomogeneousMatrix _Container, CVectorExpression _Vector> requires CMatrixContainer<_Container> && (_Container::col_count - 1 == vector_traits<_Vector>::dimension)
constexpr _Container& translate_assign(_Container& container, const _Vector& vector) {
	for (size_t i = 0; i < vector_traits<_Vector>::col_count; i++)
	{
		container().assign(i, _Container::col_count - 1, container()(i, _Container::col_count - 1) + vector()(i));
	}
	return container;
}

NGS_MLA_END
