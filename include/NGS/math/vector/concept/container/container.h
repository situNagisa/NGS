#pragma once

#include "../expression.h"
#include "./concept.h"
#include "./functor.h"

NGS_MATH_VECTOR_BEGIN

template<class _Derived>
struct vector_container : vector_expression<_Derived>
{
	NGS_MPL_ENVIRON(vector_container);
public:
	NGS_MPL_INHERIT_TYPE(expression_type, base_type);
public:
	using base_type::base_type;
	constexpr vector_container() = default;
	//constexpr explicit(false) vector_container(auto&& vector)
	//	requires functor::copyable<expression_type,decltype(vector)>
	//{
	//	functor::copy(base_type::_derived(), NGS_PERFECT_FORWARD(vector));
	//}

	constexpr auto&& operator=(auto&& expr)
		requires functor::copyable<expression_type, decltype(expr)>
	{
		functor::copy(base_type::_derived(), NGS_PERFECT_FORWARD(expr));
		return base_type::_derived();
	}
};

NGS_MATH_VECTOR_END
