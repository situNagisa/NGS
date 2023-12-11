#pragma once

#include "./defined.h"

NGS_LIB_BEGIN

template<class _BitType>
struct flag
{
	NGS_MPL_ENVIRON_BEGIN(flag);
public:
	using bit_type = _BitType;
	using value_type = std::underlying_type_t<bit_type>;

	constexpr flag() = default;
	constexpr explicit flag(value_type v) : _value(v) {}
	constexpr flag(bit_type bit) : _value(static_cast<value_type>(bit)) {}
	constexpr flag(const self_type&) = default;

	constexpr auto&& value() { return _value; }
	constexpr auto&& value()const { return _value; }

	constexpr self_type& operator=(const self_type&) = default;
	//constexpr auto operator<=>(const self_type&) const = default;

	constexpr auto operator&(const self_type& other)const { return self_type(_value & other._value); }
	constexpr auto operator|(const self_type& other)const { return self_type(_value | other._value); }
	constexpr auto operator^(const self_type& other)const { return self_type(_value ^ other._value); }
	constexpr auto operator~()const { return self_type(~_value); }

	constexpr auto operator&=(const self_type& other) { _value &= other._value; return *this; }
	constexpr auto operator|=(const self_type& other) { _value |= other._value; return *this; }
	constexpr auto operator^=(const self_type& other) { _value ^= other._value; return *this; }

	explicit constexpr operator bool()const { return static_cast<bool>(_value); }
	explicit constexpr operator value_type()const { return _value; }
public:
	// for non-type template parameter
	value_type _value{};
};


NGS_LIB_END