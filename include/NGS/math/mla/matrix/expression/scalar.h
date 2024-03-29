﻿#pragma once

#include "NGS/math/mla/matrix/expression/expression.h"

NGS_MLA_BEGIN

template<ccpt::uint _Row, ccpt::uint _Col, class  _ElementType>
class NGS_DLL_API  MatrixScalarExpression : public MatrixExpression<MatrixScalarExpression<_Row, _Col, _ElementType>> {
	NGS_MPL_ENVIRON(MatrixScalarExpression);
public:
	using element_type = _ElementType;
	constexpr static size_t row_count = _Row::value;
	constexpr static size_t col_count = _Col::value;
	constexpr static size_t element_count = row_count * col_count;

	constexpr explicit MatrixScalarExpression(element_type scalar) noexcept
		: _scalar(scalar)
	{}

	using base_type::operator();
	constexpr element_type operator()(size_t row_index, size_t col_index)const { return _scalar; }

private:
	element_type _scalar;
};
template<size_t _Row, size_t _Col, class  _ElementType>
using matrix_scalar_expression_t = MatrixScalarExpression<std::integral_constant<size_t, _Row>, std::integral_constant<size_t, _Col>, _ElementType>;

NGS_CCPT_VERIFY(CMatrixExpression, matrix_scalar_expression_t<3, 3, int>);



NGS_MLA_END
