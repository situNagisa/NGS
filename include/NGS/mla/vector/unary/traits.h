#pragma once

#include "NGS/mla/vector/unary/functor.h"
#include "NGS/mla/vector/unary/unary.h"

NGS_MLA_BEGIN

template<CVectorExpression _Expression, CScalarUnaryFunctor _Functor>
struct vector_unary_scalar_traits {
	using original_expression_type = _Expression;
	using functor_type = _Functor;
	using expression_type = VectorUnary<original_expression_type, VectorUnaryScalarFunctor<original_expression_type, functor_type>>;
};

template<CVectorExpression _Expression, template<class>class _ScalarFunctor>
using vector_unary_scalar_traits_t = typename vector_unary_scalar_traits<_Expression, _ScalarFunctor<typename _Expression::element_type>>::expression_type;

NGS_MLA_END
