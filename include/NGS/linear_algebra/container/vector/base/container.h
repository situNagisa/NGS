#pragma once

#include "./expression.h"

NGS_MATH_LA_VECTOR_CONTAINER_BEGIN

template<class _Derived>
struct vector_container : vector_expression<_Derived>
{
	NGS_MPL_ENVIRON(vector_container);
public:
	NGS_MPL_INHERIT_TYPE(expression_type, base_type);
public:
	using base_type::base_type;
	constexpr vector_container() = default;

	constexpr auto&& operator=(auto&& expr)
		requires concepts::vectors::copyable<expression_type&, decltype(expr)>
	{
		adapters::vectors::copy(base_type::_derived(), NGS_PP_PERFECT_FORWARD(expr));
		return base_type::_derived();
	}
};


NGS_MATH_LA_VECTOR_CONTAINER_END