#pragma once

#include "NGS/mla/vector/expression.h"
#include "NGS/mla/vector/binary/functor.h"

NGS_MLA_BEGIN

template<CVectorExpression _Expression1, CVectorExpression _Expression2, CVectorBinaryFunctor<_Expression1, _Expression2> _Functor>
	requires (_Expression1::dimension == _Expression2::dimension)
class VectorBinary : public VectorExpression<VectorBinary<_Expression1, _Expression2, _Functor>> {
private:
	using base_type = typename VectorBinary::self_type;
protected:
	using self_type = VectorBinary<_Expression1, _Expression2, _Functor>;
public:
	using expression_type = typename base_type::expression_type;
	using functor_type = _Functor;

	using element_type = mpl::promote_t<typename _Expression1::element_type, typename _Expression2::element_type>;
	constexpr static size_t dimension = _Expression1::dimension;

	constexpr explicit VectorBinary(const _Expression1& expression1, const _Expression2& expression2) noexcept
		: _expression1(expression1)
		, _expression2(expression2)
	{}

	using base_type::operator();
	constexpr element_type operator ()(size_t i) { return functor_type::apply(_expression1, _expression2, i); }
	constexpr element_type operator()(size_t i)const { return functor_type::apply(_expression1, _expression2, i); }

private:
	const _Expression1& _expression1;
	const _Expression2& _expression2;
};
//verify

NGS_MLA_END
