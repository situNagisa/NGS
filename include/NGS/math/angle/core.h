#pragma once

#include "./defined.h"

NGS_MATH_ANGLE_BEGIN

template<std::floating_point _ValueType>
struct angle
{
	using self_type = angle;
	using value_type = _ValueType;

	constexpr angle() = default;
	constexpr angle(const value_type& value) : data(value) {}

	constexpr explicit(true) operator value_type() const { return data; }

	constexpr auto&& value() { return data; }
	constexpr auto&& value() const { return data; }

	constexpr self_type& operator=(const self_type&) = default;
	constexpr self_type& operator+=(const self_type& value) { data += value.value(); return *this; }
	constexpr self_type& operator-=(const self_type& value) { data -= value.value(); return *this; }
	constexpr self_type& operator*=(const self_type& value) { data *= value.value(); return *this; }
	constexpr self_type& operator/=(const self_type& value) { data /= value.value(); return *this; }

	constexpr self_type operator+(const self_type& value) const { return self_type(data + value.value()); }
	constexpr self_type operator-(const self_type& value) const { return self_type(data - value.value()); }
	constexpr self_type operator*(const self_type& value) const { return self_type(data * value.value()); }
	constexpr self_type operator/(const self_type& value) const { return self_type(data / value.value()); }

	constexpr void normalized() { data = remainder(data,2 * std::numbers::pi); }
	constexpr self_type normalized() const { return self_type(remainder(data,2 * std::numbers::pi)); }

	constexpr self_type& operator%=(const self_type& value) { data = remainder(data, value.value()); return *this; }
	constexpr self_type operator%(const self_type& value) const { return self_type(remainder(data, value.value())); }
public:
	value_type data{};
};

template<std::floating_point _ValueType>
constexpr auto sin(const angle<_ValueType>& value) { return std::sin(value.value()); }

template<std::floating_point _ValueType>
constexpr auto cos(const angle<_ValueType>& value) { return std::cos(value.value()); }

template<std::floating_point _ValueType>
constexpr auto tan(const angle<_ValueType>& value) { return std::tan(value.value()); }

template<std::floating_point _ValueType>
constexpr auto asin(const angle<_ValueType>& value) { return std::asin(value.value()); }

template<std::floating_point _ValueType>
constexpr auto acos(const angle<_ValueType>& value) { return std::acos(value.value()); }

template<std::floating_point _ValueType>
constexpr auto atan(const angle<_ValueType>& value) { return std::atan(value.value()); }

NGS_MATH_ANGLE_END