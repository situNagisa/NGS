#pragma once

#include "./defined.h"

NGS_LIB_MODULE_BEGIN

struct extent
{
	NGS_PP_INJECT_BEGIN(extent);
public:
	constexpr extent() = default;
	constexpr explicit(true) extent(::std::size_t value) : _value(value) {}

	constexpr auto&& value() const { return _value; }

	constexpr bool is_dynamic() const { return _value == ::std::dynamic_extent; }
	constexpr bool is_adaptor() const { return _value == 0; }
	constexpr bool is_static() const { return !is_dynamic() && !is_adaptor(); }

	friend constexpr auto operator<=>(const self_type&, const self_type&) = default;

	friend constexpr bool operator==(const self_type& left, const self_type& right)
	{
		return (left._value == right._value) || ((left.is_dynamic() || right.is_dynamic()) || (left.is_adaptor() || right.is_adaptor()));
	}

	friend constexpr self_type operator*(const self_type& left, const self_type& right)
	{
		NGS_ASSERT_IF_CONSTEVAL(left == right || )
		return ::std::max(left, right);
	}

	

	::std::size_t _value{};
};

inline constexpr extent dynamic_extent{ ::std::dynamic_extent };
inline constexpr extent adaptor_extent{ 0 };



NGS_LIB_MODULE_END