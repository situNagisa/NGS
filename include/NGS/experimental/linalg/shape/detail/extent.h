#pragma once

#include "./defined.h"

NGS_LIB_MODULE_BEGIN

using static_extent_t = ::std::size_t;

struct extent
{
	NGS_PP_INJECT_BEGIN(extent);
public:
	using value_type = static_extent_t;

	constexpr extent() = default;
	constexpr explicit(true) extent(value_type value) : _value(value) {}

	constexpr auto&& value(this const self_type& self) { return self._value; }

	constexpr bool is_dynamic(this const self_type& self) { return self._value == static_cast<value_type>(::std::dynamic_extent); }
	constexpr bool is_adaptor(this const self_type& self) { return self._value == static_cast<value_type>(0); }
	constexpr bool is_static(this const self_type& self) { return !self.is_dynamic() && !self.is_adaptor(); }

	friend constexpr auto operator<=>(const self_type&, const self_type&) = default;

	friend constexpr bool operator==(const self_type& left, const self_type& right)
	{
		return (left._value == right._value);
	}

	value_type _value{};
};

inline constexpr auto dynamic_extent = extent{ static_cast<static_extent_t>(::std::dynamic_extent) };
inline constexpr auto adaptor_extent = extent{ static_cast<static_extent_t>(0) };

constexpr auto dynamic_equal(const extent& left, const extent& right)
{
	return (left == right) || left.is_dynamic() || right.is_dynamic();
}

NGS_LIB_MODULE_END