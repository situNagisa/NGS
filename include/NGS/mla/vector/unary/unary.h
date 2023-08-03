#pragma once

#include "NGS/mla/vector/expression.h"
#include "NGS/mla/vector/unary/functor.h"

NGS_MLA_BEGIN

template<CVectorExpression _Expression, CVectorUnaryFunctor<_Expression> _Functor>
class VectorUnary : public VectorExpression<VectorUnary<_Expression, _Functor>> {
private:
	using base_type = typename VectorUnary::self_type;
protected:
	using self_type = VectorUnary<_Expression, _Functor>;
public:
	using expression_type = typename base_type::expression_type;

	using functor_type = _Functor;

	using element_type = typename _Expression::element_type;
	constexpr static size_t dimension = _Expression::dimension;

	constexpr explicit VectorUnary(const _Expression& expression) noexcept
		: _expression(expression)
	{}

	using base_type::operator();
	constexpr element_type operator ()(size_t i) { return functor_type::apply(_expression, i); }
	constexpr element_type operator()(size_t i)const { return functor_type::apply(_expression, i); }

private:
	const _Expression& _expression;
};
//verify

NGS_MLA_END
