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
#include "NGS/math/mla/matrix/binary/operator/multiplies/multiplicative.h"

NGS_MLA_BEGIN

namespace tag {

struct vector_multiplies_matrix : unknown {};
struct matrix_multiplies_vector : unknown {};

}

template<class _Type>
concept CMatrixVectorMultipliesMethod =
std::same_as<std::remove_cvref_t<_Type>, tag::vector_multiplies_matrix> ||
std::same_as<std::remove_cvref_t<_Type>, tag::matrix_multiplies_vector>;

template<CMatrixExpression _Matrix, CVectorExpression _Vector,
	CMatrixVectorMultipliesMethod _Method
>
class  MatrixVectorMultiplies : public VectorExpression<MatrixVectorMultiplies<_Matrix, _Vector, _Method>> {
	NGS_MPL_ENVIRON(MatrixVectorMultiplies);
public:
	using expression_type = typename base_type::expression_type;
private:
	using matrix_closure_type = typename matrix_traits<_Matrix>::closure_type;
	using vector_closure_type = typename vector_traits<_Vector>::closure_type;
public:
	using element_type = mpl::promote_t<typename matrix_traits<_Matrix>::element_type, typename vector_traits<_Vector>::element_type>;

	constexpr static size_t complexity = matrix_traits<_Matrix>::complexity + vector_traits<_Vector>::complexity + 1;
	constexpr static size_t dimension = vector_traits<_Vector>::dimension;

	constexpr explicit MatrixVectorMultiplies(matrix_closure_type matrix, vector_closure_type vector) noexcept
		: _matrix(matrix)
		, _vector(vector)
	{}

	using base_type::operator();
	constexpr element_type operator()(size_t index)const {
		if constexpr (std::same_as<_Method, tag::matrix_multiplies_vector>) {
			return product_inner(_vector(), row(_matrix(), index));
		}
		else {
			return product_inner(_vector(), column(_matrix(), index));
		}
	}
private:
	matrix_closure_type _matrix;
	vector_closure_type _vector;
};

template<CMatrixExpression _Matrix, CVectorExpression _Vector>
	requires CMultiplicative<_Matrix,_Vector>
constexpr auto multiplies_vector(const _Matrix& matrix, const _Vector& vector) {
	return MatrixVectorMultiplies<_Matrix, _Vector, tag::matrix_multiplies_vector>(matrix, vector);
}
template<CMatrixExpression _Matrix, CVectorExpression _Vector>
	requires CMultiplicative<_Vector, _Matrix>
constexpr auto multiplies_vector(const _Vector& vector, const _Matrix& matrix) {
	return MatrixVectorMultiplies<_Matrix, _Vector, tag::vector_multiplies_matrix>(matrix, vector);
}

//Æë´Î

template<CMatrixExpression _Matrix, CVectorExpression _Vector>
	requires CMultiplicative<_Matrix, VectorHomogenousExpression<_Vector>>
constexpr auto multiplies_vector(const _Matrix& matrix, const _Vector& vector) {
	using vector_t = VectorHomogenousExpression<_Vector>;
	return multiplies_vector(matrix, vector_t(vector));
}
template<CMatrixExpression _Matrix, CVectorExpression _Vector>
	requires CMultiplicative<VectorHomogenousExpression<_Vector>, _Matrix>
constexpr auto multiplies_vector(const _Vector& vector, const _Matrix& matrix) {
	using vector_t = VectorHomogenousExpression<_Vector>;
	return multiplies_vector(vector_t(vector), matrix);
}

template<CMatrixContainer _Container, CVectorExpression _Vector>
	requires CMultiplicative<_Container, _Vector> || CMultiplicative<_Container, VectorHomogenousExpression<_Vector>>
_Container & multiplies_assign(_Container & container, const _Vector & vector) { return container.assign(multiplies_vector(container, vector)); }

template<CMatrixExpression _Matrix, CVectorExpression _Vector>
	requires CMultiplicative<_Matrix, _Vector> || CMultiplicative<_Matrix, VectorHomogenousExpression<_Vector>>
constexpr auto operator*(const _Matrix & matrix, const _Vector & vector) { return multiplies_vector(matrix, vector); }

template<CMatrixExpression _Matrix, CVectorExpression _Vector>
	requires CMultiplicative<_Vector, _Matrix> || CMultiplicative<VectorHomogenousExpression<_Vector>, _Matrix>
constexpr auto operator*(const _Vector & vector, const _Matrix & matrix) { return multiplies_vector(vector, matrix); }

template<CMatrixContainer _Container, CVectorExpression _Vector>
	requires CMultiplicative<_Container, _Vector> || CMultiplicative<_Container, VectorHomogenousExpression<_Vector>>
_Container & operator*=(_Container & container, const _Vector & vector) { return multiplies_assign(container, vector); }


NGS_MLA_END
