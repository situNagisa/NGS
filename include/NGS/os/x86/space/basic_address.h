#pragma once

#include "../pointer.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

struct basic_address
{
	NGS_MPL_ENVIRON_BEGIN(basic_address);
public:
	using underlying_type = pointer_t;

	constexpr basic_address() = default;
	constexpr explicit(true) basic_address(underlying_type value) : _value(value) {}

	constexpr auto value() const { return _value; }

	constexpr bool operator==(const self_type&) const = default;
	constexpr auto operator<=>(const self_type&) const = default;

	constexpr self_type& operator+=(const basic_address& address) { _value += address.value(); return *this; }
	constexpr self_type& operator+=(const underlying_type& address) { _value += address; return *this; }
	constexpr self_type& operator-=(const basic_address& address) { _value -= address.value(); return *this; }
	constexpr self_type& operator-=(const underlying_type& address) { _value -= address; return *this; }

	underlying_type _value{};
};

template<::std::derived_from<basic_address> T>
constexpr decltype(auto) operator+(const T& left, const basic_address& right) { return T{ left.value() + right.value() }; }
template<::std::derived_from<basic_address> T>
constexpr decltype(auto) operator+(const T& left, const typename type_traits::object_t<T>::underlying_type& right) { return T{ left.value() + right }; }
template<::std::derived_from<basic_address> T>
constexpr decltype(auto) operator+(const typename type_traits::object_t<T>::underlying_type& left, const T& right) { return T{ left + right.value() }; }


template<::std::derived_from<basic_address> T>
constexpr decltype(auto) operator-(const T& left, const basic_address& right) { return T{ left.value() - right.value() }; }
template<::std::derived_from<basic_address> T>
constexpr decltype(auto) operator-(const T& left, const typename type_traits::object_t<T>::underlying_type& right) { return T{ left.value() - right }; }
template<::std::derived_from<basic_address> T>
constexpr decltype(auto) operator-(const typename type_traits::object_t<T>::underlying_type& left, const T& right) { return T{ left - right.value() }; }

NGS_LIB_MODULE_END