#pragma once

#include "NGS/math/mla/matrix/expression/square.h"

NGS_MLA_BEGIN

template<ccpt::UInt _Dim, class _ElementType>
struct IdentityMatrix : SquareMatrix<IdentityMatrix<_Dim, _ElementType>, _Dim> {
private:
	using base_type = IdentityMatrix::self_type;
protected:
	using self_type = IdentityMatrix<_Dim, _ElementType>;
public:
	using element_type = _ElementType;
	NGS_minherit(row_count, base_type);
	NGS_minherit(col_count, base_type);

	using base_type::operator();
	constexpr element_type operator()(size_t row_index, size_t col_index) const {
		return row_index == col_index ? element_type(1) : element_type(0);
	}
};
template<size_t _Dimension, class _ElementType>
using identity_matrix_t = IdentityMatrix<std::integral_constant<size_t, _Dimension>, _ElementType>;
template<size_t _Dimension, class _ElementType>
constexpr identity_matrix_t<_Dimension, _ElementType> identity_matrix_v{};

NGS_CCPT_VERIFY(CSquareMatrix, identity_matrix_t<3, int>);

NGS_MLA_END