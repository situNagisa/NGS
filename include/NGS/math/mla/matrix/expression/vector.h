#pragma once

#include "NGS/math/mla/matrix/expression/concept.h"
#include "NGS/math/mla/vector/expression/concept.h"
#include "NGS/math/mla/matrix/traits.h"
#include "NGS/math/mla/vector/traits.h"
#include "NGS/math/mla/matrix/expression/expression.h"
#include "NGS/math/mla/vector/expression/expression.h"

NGS_MLA_BEGIN

template<CVectorExpression _Expression, CMatrixLayout _Layout = tag::row>
struct MatrixVectorExpression : MatrixExpression<MatrixVectorExpression<_Expression, _Layout>> {
private:
	using base_type = MatrixVectorExpression::self_type;
protected:
	using self_type = MatrixVectorExpression<_Expression, _Layout>;
	using closure_type = typename vector_traits<_Expression>::closure_type;
public:
	using element_type = typename vector_traits<_Expression>::element_type;
	using layout_category = _Layout;

	constexpr static size_t row_count = is_col_major<layout_category> ? vector_traits<_Expression>::dimension : 1;
	constexpr static size_t col_count = is_row_major<layout_category> ? vector_traits<_Expression>::dimension : 1;
	constexpr static size_t element_count = row_count * col_count;

	constexpr explicit MatrixVectorExpression(closure_type expression)
		: _expression(expression)
	{}

	using base_type::operator();
	constexpr element_type operator()(size_t row_index, size_t col_index)const {
		return _expression()(layout_category::transform(row_index, col_index, row_count, col_count));
	}
private:
	closure_type _expression;
};

NGS_MLA_END
