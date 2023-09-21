#pragma once

#include "NGS/math/mla/matrix/expression/expression.h"
#include "NGS/math/mla/vector/unary/unary.h"

NGS_MLA_BEGIN

template<CMatrixExpression _Expression, CMatrixLayout _Layout = tag::row>
class NGS_API  AsVectorUnary : public VectorExpression<AsVectorUnary<_Expression, _Layout>> {
	NGS_menvironment(AsVectorUnary);
public:
	NGS_minherit_t(expression_type, base_type);
	using expression_closure_type = typename matrix_traits<_Expression>::closure_type;
	using element_type = typename matrix_traits<_Expression>::element_type;
	using layout_type = _Layout;
	constexpr static size_t dimension = matrix_traits<_Expression>::row_count * matrix_traits<_Expression>::col_count;
	constexpr static size_t complexity = matrix_traits<_Expression>::complexity + 1;

	constexpr explicit AsVectorUnary(expression_closure_type expression) noexcept
		: _expression(expression)
	{}

	using base_type::operator();
	constexpr element_type operator()(size_t i)const {
		auto [row_index, col_index] = layout_type::inverse_transform(i, matrix_traits<_Expression>::row_count, matrix_traits<_Expression>::col_count);
		return _expression(row_index, col_index);
	}

private:
	expression_closure_type _expression;
};

template<CMatrixLayout _Layout = tag::row, CMatrixExpression _Expression>
constexpr auto as_vector(const _Expression& expression) {
	return AsVectorUnary<_Expression, _Layout>(expression);
}

NGS_MLA_END
