#pragma once

#include "../expression.h"
#include "./concept.h"
#include "./functor.h"

NGS_MATH_MATRIX_BEGIN

template<class _Derived>
struct matrix_container : matrix_expression<_Derived>
{
	NGS_MPL_ENVIRON(matrix_container);
public:
	NGS_MPL_INHERIT_TYPE(expression_type, base_type);
public:
	using base_type::base_type;
	constexpr matrix_container() = default;

	constexpr auto&& operator=(auto&& matrix)
		requires functor::copyable<expression_type, decltype(matrix)>
	{
		functor::copy(base_type::_derived(), NGS_PERFECT_FORWARD(matrix));
		return base_type::_derived();
	}
};

NGS_MATH_MATRIX_END
