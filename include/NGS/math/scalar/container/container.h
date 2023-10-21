#pragma once

#include "../expression/expression.h"
#include "./assign.h"
#include "./tag.h"

NGS_MATH_SCALAR_BEGIN

template<ccpt::CRPT _Derived,class _ValueType>
struct scalar_container : scalar_expression<_Derived>
{
	NGS_MPL_ENVIRON(scalar_container);
public:
	NGS_MPL_INHERIT_TYPE(expression_type, base_type);
	using expression_category = scalar_container_tag;
	using value_type = _ValueType;

public:
	constexpr scalar_container() = default;
	constexpr explicit(NGS_MATH_SCALAR_EXPLICIT) scalar_container(const value_type& element)
	{
		assign(base_type::_derived(), element);
	}
	constexpr explicit(NGS_MATH_SCALAR_EXPLICIT) scalar_container(const CScalarExpression auto& scalar)
	{
		assign(base_type::_derived(), scalar);
	}

	constexpr auto&& operator=(const CScalarExpression auto& scalar)
	{
		assign(base_type::_derived(), scalar);
		return base_type::_derived();
	}
	constexpr auto&& operator=(const self_type& other)
	{
		assign(base_type::_derived(), other._derived());
		return base_type::_derived();
	}
	constexpr auto&& operator=(const value_type& element)
	{
		assign(base_type::_derived(), element);
		return base_type::_derived();
	}
};

NGS_MATH_SCALAR_END