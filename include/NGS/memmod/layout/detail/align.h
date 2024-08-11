#pragma once

#include "./defined.h"

NGS_LIB_MODULE_BEGIN

template<class T>
concept align = ::std::unsigned_integral<T>;

enum class policy
{
	deduce,
	recommend,
	force,
};

struct basic_policy
{
	policy policy;
	::std::size_t value;
};

template<class T>
concept align_policy = ::std::derived_from<T, basic_policy>;

constexpr decltype(auto) deduce() { return basic_policy{ policy::deduce, 0 }; }
constexpr decltype(auto) recommend(::std::size_t value) { return basic_policy{ policy::recommend, ::std::bit_ceil(value) }; }
constexpr decltype(auto) force(::std::size_t value) { return basic_policy{ policy::force, ::std::bit_ceil(value) }; }

template<basic_policy Policy>
constexpr auto align_of(const ::std::ranges::input_range auto& aligns)
	requires align<::std::ranges::range_value_t<decltype(aligns)>>
{
	if constexpr (Policy.policy == policy::deduce)
	{
		if (::std::ranges::empty(aligns))
			return static_cast<::std::ranges::range_value_t<decltype(aligns)>>(1);
		return ::std::ranges::max(aligns);
	}
	else if constexpr (Policy.policy == policy::recommend)
	{
		return ::std::ranges::max(NGS_LIB_MODULE_NAME::align_of<NGS_LIB_MODULE_NAME::deduce()>(aligns), static_cast<::std::ranges::range_value_t<decltype(aligns)>>(Policy.value));
	}
	else if constexpr (Policy.policy == policy::force)
	{
		static_assert(Policy.value == 1, "Forcing alignment is not supported.");
		return static_cast<::std::ranges::range_value_t<decltype(aligns)>>(Policy.value);
	}
}

constexpr bool is_valid_align(const align auto& align_, ::std::size_t default_align_ = 1)
{
	return (::std::has_single_bit(align_) && align_ >= default_align_);
}

NGS_LIB_MODULE_END