#pragma once

#include "./defined.h"

NGS_LIB_MODULE_BEGIN

constexpr decltype(auto) as_vector(::std::ranges::sized_range auto&& range)
{
	using range_type = std::vector<::std::ranges::range_value_t<decltype(range)>>;
	range_type result{ ::std::ranges::size(range) };
	::std::ranges::transform(range, result.begin(), [](auto&& value) { return ::std::forward<decltype(value)>(value); });
	return result;
}

NGS_LIB_MODULE_END