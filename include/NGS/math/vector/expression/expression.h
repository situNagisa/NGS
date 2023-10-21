#pragma once

#include "./concept.h"
#include "./access.h"
#include "./dimension.h"
#include "./value_type.h"

NGS_MATH_VECTOR_BEGIN

template<class _Derived>
struct vector_expression : yap::expression<_Derived>
{
	NGS_MPL_ENVIRON(vector_expression);
public:
	constexpr static size_t dimension = 0;

	constexpr decltype(auto) operator()(size_t index)
	{
		return functor::access(base_type::_derived(), index);
	}
	constexpr decltype(auto) operator()(size_t index)const
	{
		return functor::access(base_type::_derived(), index);
	}
};

NGS_MATH_VECTOR_END
