#pragma once

#include "NGS/mla/vector/binary/functor.h"
#include "NGS/mla/vector/binary/binary.h"

NGS_MLA_BEGIN

template<CVectorExpression _Expression1, CVectorExpression _Expression2, CScalarBinaryFunctor _Functor>
struct vector_binary_scalar_traits {
	using original_expression_type1 = _Expression1;
	using original_expression_type2 = _Expression2;
	using functor_type = _Functor;
	using expression_type = VectorBinary<original_expression_type1, original_expression_type2, VectorBinaryScalarFunctor<original_expression_type1, original_expression_type2, functor_type>>;
};

template<CVectorExpression _Expression1, CVectorExpression _Expression2, template<class, class>class _ScalarFunctor>
using vector_binary_scalar_traits_t = typename vector_binary_scalar_traits<_Expression1, _Expression2, _ScalarFunctor<typename _Expression1::element_type, typename _Expression2::element_type>>::expression_type;

NGS_MLA_END