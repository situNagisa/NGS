#pragma once

#include "NGS/math/mla/vector/expression/expression.h"
#include "NGS/math/mla/vector/expression/container.h"
#include "NGS/math/mla/vector/binary/functor.h"

NGS_MLA_BEGIN

template<CVectorExpression _Expression1, CVectorExpression _Expression2, CVectorBinaryFunctor<_Expression1, _Expression2> _Functor>
class VectorBinary : public VectorExpression<VectorBinary<_Expression1, _Expression2, _Functor>> {
private:
	using base_type = typename VectorBinary::self_type;
protected:
	using self_type = VectorBinary<_Expression1, _Expression2, _Functor>;
public:
	using expression_type = typename base_type::expression_type;
private:
	using functor_type = _Functor;
	using original_expression_type1 = typename vector_traits<_Expression1>::original_type;
	using original_expression_type2 = typename vector_traits<_Expression2>::original_type;

	using expression_closure_type1 = typename vector_traits<_Expression1>::closure_type;
	using expression_closure_type2 = typename vector_traits<_Expression2>::closure_type;
public:

	using element_type = mpl::promote_t<typename vector_traits<_Expression1>::element_type, typename vector_traits<_Expression2>::element_type>;
	static_assert(vector_traits<_Expression1>::dimension == vector_traits<_Expression2>::dimension, "the dimension should same");
	constexpr static size_t dimension = vector_traits<_Expression1>::dimension;
	constexpr static size_t complexity = vector_traits<_Expression1>::complexity + vector_traits<_Expression2>::complexity + 1;

	constexpr explicit VectorBinary(expression_closure_type1 expression1, expression_closure_type2 expression2) noexcept
		: _expression1(expression1)
		, _expression2(expression2)
	{}

	using base_type::operator();
	constexpr element_type operator()(size_t i)const { return functor_type::apply(_expression1, _expression2, i); }

private:
	expression_closure_type1 _expression1;
	expression_closure_type2 _expression2;
};
//verify

NGS_MLA_END
