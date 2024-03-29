﻿#pragma once

#include "NGS/math/mla/vector/expression/expression.h"
#include "NGS/math/mla/vector/expression/container.h"
#include "NGS/math/mla/vector/unary/functor.h"
#include "NGS/math/mla/vector/traits.h"

NGS_MLA_BEGIN

template<CVectorExpression _Expression, CVectorUnaryFunctor<_Expression> _Functor>
class NGS_DLL_API  VectorUnary : public VectorExpression<VectorUnary<_Expression, _Functor>> {
	NGS_MPL_ENVIRON(VectorUnary);
public:
	using expression_type = typename base_type::expression_type;
private:
	using functor_type = _Functor;
	using original_expression_type = typename vector_traits<_Expression>::original_type;
	using expression_closure_type = typename vector_traits<_Expression>::closure_type;
public:
	using element_type = typename vector_traits<_Expression>::element_type;
	constexpr static size_t dimension = vector_traits<_Expression>::dimension;
	constexpr static size_t complexity = vector_traits<_Expression>::complexity + 1;

	constexpr explicit VectorUnary(expression_closure_type expression) noexcept
		: _expression(expression)
	{}

	using base_type::operator();
	constexpr element_type operator()(size_t i)const { return functor_type::apply(_expression, i); }

private:
	expression_closure_type _expression;
};
//verify

NGS_MLA_END
