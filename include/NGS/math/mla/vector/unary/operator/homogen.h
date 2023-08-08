#pragma once

#include "NGS/math/mla/vector/expression/expression.h"
#include "NGS/math/mla/vector/traits.h"

NGS_MLA_BEGIN

template<CVectorExpression _Expression>
class VectorHomogenousExpression : public VectorExpression<VectorHomogenousExpression<_Expression>> {
private:
	using base_type = VectorHomogenousExpression::self_type;
protected:
	using self_type = VectorHomogenousExpression;
	using closure_type = typename vector_traits<_Expression>::closure_type;
public:
	constexpr static size_t dimension = vector_traits<_Expression>::dimension + 1;
	using element_type = typename vector_traits<_Expression>::element_type;

	constexpr VectorHomogenousExpression(closure_type expression)
		: _expression(expression)
	{}

	using base_type::operator();
	constexpr element_type operator()(size_t index)const {
		if (index < dimension - 1)
			return _expression()(index);
		return element_type(1);
	}
private:
	closure_type _expression;
};

NGS_MLA_END
