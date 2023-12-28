#pragma once

#include "./concept.h"
#include "../trait.h"

NGS_MATH_SCALAR_BEGIN

template<class _ValueType>
struct scalar : scalar_container<scalar<_ValueType>, _ValueType>
{
	NGS_MPL_ENVIRON(scalar);
public:
	NGS_MPL_INHERIT_TYPE(value_type, base_type);

	using base_type::base_type;
	constexpr scalar() = default;
	constexpr explicit(NGS_MATH_SCALAR_EXPLICIT) scalar(const value_type& v) noexcept
		: data(v)
	{}

	using base_type::operator=;

	constexpr auto&& value() { return data; }
	constexpr auto&& value()const { return data; }

	constexpr void assign(const value_type& v) { data = v; }
public:
	value_type data{};
};

template<class _ValueType>
scalar(_ValueType) -> scalar<_ValueType>;

NGS_MATH_SCALAR_END