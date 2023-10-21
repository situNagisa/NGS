#pragma once

#include "./defined.h"
#include "./expression/concept.h"

NGS_MATH_SCALAR_BEGIN

template<class>
struct scalar_traits{};

template<CScalarExpression _Scalar>
struct scalar_traits<_Scalar>
{
	using expression_type = typename std::remove_reference_t<_Scalar>::expression_type;
	using closure_type = expression_type;

	using element_type = typename expression_type::element_type;
};

NGS_MATH_SCALAR_END