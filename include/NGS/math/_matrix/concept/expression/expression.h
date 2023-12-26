#pragma once

#include "./concept.h"
#include "./trait.h"
#include "./functor.h"

NGS_MATH_MATRIX_BEGIN

template<class _Derived>
struct matrix_expression : yap::expression<_Derived>
{
	NGS_MPL_ENVIRON(matrix_expression);
public:

	constexpr decltype(auto) operator()(size_t row, size_t column)
	{
		return functor::access(base_type::_derived(), row, column);
	}
	constexpr decltype(auto) operator()(size_t row, size_t column)const
	{
		return functor::access(base_type::_derived(), row, column);
	}
};

NGS_MATH_MATRIX_END
