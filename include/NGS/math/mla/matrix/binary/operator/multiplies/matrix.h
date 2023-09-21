#pragma once

#include "NGS/math/mla/matrix/binary/binary.h"
#include "NGS/math/mla/scalar/binary.h"
#include "NGS/math/mla/matrix/expression/container.h"
#include "NGS/math/mla/matrix/expression/scalar.h"
#include "NGS/math/mla/vector/binary.h"
#include "NGS/math/mla/vector/expression/concept.h"
#include "NGS/math/mla/matrix/unary/operator/access.h"
#include "NGS/math/mla/matrix/expression/vector.h"
#include "NGS/math/mla/matrix/binary/operator/multiplies/multiplicative.h"

NGS_MLA_BEGIN

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

template<CMatrixExpression _Left, CMatrixExpression _Right> requires CMultiplicative<_Left,_Right>
constexpr auto multiplies(const _Left& left, const _Right& right) {
	using binary_t = matrix_binary_t<_Left, _Right, MatrixMultipliesFunctor<_Left, _Right>>;
	return binary_t(left, right);
}

template<CMatrixExpression _Left, CMatrixExpression _Right> requires CMultiplicative<_Left, _Right>
constexpr auto operator*(const _Left& left, const _Right& right) { return multiplies(left, right); }

template<CMatrixContainer _Container, CMatrixExpression _Right> requires CMultiplicative<_Container, _Right>
_Container& multiplies_assign(_Container& container, const _Right& right) { return container.assign(multiplies(container, right)); }
template<CMatrixContainer _Container, CMatrixExpression _Right> requires CMultiplicative<_Container, _Right>
_Container& operator*=(_Container& container, const _Right& right) { return multiplies_assign(container, right); }

NGS_MLA_END
