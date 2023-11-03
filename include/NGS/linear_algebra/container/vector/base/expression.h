#pragma once

#include "../defined.h"

NGS_MATH_LA_VECTOR_CONTAINER_BEGIN

using adapters::vectors::index_t;
using adapters::vectors::dimension_t;

template<class _Derived>
struct vector_expression : yap::expression<_Derived>
{
	NGS_MPL_ENVIRON(vector_expression);
public:
	constexpr static dimension_t dimension = 0;

	constexpr decltype(auto) operator()(index_t index)
	{
		return adapters::vectors::access(base_type::_derived(), index);
	}
	constexpr decltype(auto) operator()(index_t index)const
	{
		return adapters::vectors::access(base_type::_derived(), index);
	}
};

NGS_MATH_LA_VECTOR_CONTAINER_END