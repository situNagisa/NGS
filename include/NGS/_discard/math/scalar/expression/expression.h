#pragma once

#include "./concept.h"
#include "./evaluate.h"
#include "./value.h"

NGS_MATH_SCALAR_BEGIN

template<ccpt::CRPT _Derived>
struct scalar_expression : yap::expression<_Derived>
{
	NGS_MPL_ENVIRON(scalar_expression);
public:
	using expression_category = scalar_expression_tag;

	constexpr explicit(NGS_MATH_SCALAR_EXPLICIT) operator auto&&()const noexcept
	{
		return value(evaluate(base_type::_derived()));
	}
};

NGS_MATH_SCALAR_END