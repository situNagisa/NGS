#pragma once

#include "NGS/math/mla/matrix/expression/expression.h"

NGS_MLA_BEGIN

template<ccpt::uint _Row, ccpt::uint _Col, class  _ElementType>
struct NGS_API ZeroMatrix : MatrixExpression<ZeroMatrix<_Row, _Col, _ElementType>> {
	NGS_MPL_ENVIRON(ZeroMatrix);
public:
	using element_type = _ElementType;
	constexpr static size_t row_count = _Row::value;
	constexpr static size_t col_count = _Col::value;
	constexpr static size_t element_count = row_count * col_count;

	using base_type::operator();
	constexpr element_type operator()(size_t row_index, size_t col_index) const { return 0; }
};
template<size_t _Row, size_t _Col, class  _ElementType>
using zero_matrix_t = ZeroMatrix<std::integral_constant<size_t, _Row>, std::integral_constant<size_t, _Col>, _ElementType>;
template<size_t _Row, size_t _Col, class  _ElementType>
constexpr zero_matrix_t<_Row, _Col, _ElementType> zero_matrix{};

NGS_CCPT_VERIFY(CMatrixExpression, zero_matrix_t<3, 4, int>);

NGS_MLA_END