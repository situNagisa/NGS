#pragma once

#include "./defined.h"

NGS_LIB_BEGIN

template<class _Derived, class _ValueType>
struct basic_flag
{
	NGS_MPL_ENVIRON_BEGIN(basic_flag);
	using derived_type = _Derived;
	constexpr auto&& derived() { return static_cast<derived_type&>(*this); }
	constexpr auto&& derived()const { return static_cast<const derived_type&>(*this); }
public:
	using value_type = _ValueType;

	constexpr basic_flag() = default;
	constexpr explicit basic_flag(value_type v) : _value(v) {}

	constexpr auto&& value() { return _value; }
	constexpr auto&& value()const { return _value; }

	constexpr self_type& operator=(const self_type&) = default;
	constexpr bool operator==(const self_type&)const = default;
	//constexpr auto operator<=>(const self_type&) const = default;

	constexpr auto operator&(const derived_type& other)const { return derived_type(_value & other.value()); }
	constexpr auto operator|(const derived_type& other)const { return derived_type(_value | other.value()); }
	constexpr auto operator^(const derived_type& other)const { return derived_type(_value ^ other.value()); }
	constexpr auto operator~()const { return derived_type(~_value); }

	constexpr auto operator&=(const derived_type& other) { _value &= other.value(); return derived(); }
	constexpr auto operator|=(const derived_type& other) { _value |= other.value(); return derived(); }
	constexpr auto operator^=(const derived_type& other) { _value ^= other.value(); return derived(); }

	explicit constexpr operator bool()const { return static_cast<bool>(_value); }
	explicit constexpr operator value_type()const { return _value; }
public:
	// for non-type template parameter
	value_type _value{};
};

template<class _ValueType>
struct flag : basic_flag<flag<_ValueType>, _ValueType>
{
	NGS_MPL_ENVIRON(flag);
public:
	using base_type::base_type;
	using base_type::operator=;
};


NGS_LIB_END