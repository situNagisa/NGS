#pragma once

#include "./defined.h"

NGS_LIB_MODULE_BEGIN

template<class _Type = void>
constexpr decltype(auto) as_vector(::std::ranges::sized_range auto&& range)
{
	using value_type = std::conditional_t<::std::is_void_v<_Type>, ::std::ranges::range_value_t<decltype(range)>, _Type>;
	using range_type = std::vector<value_type>;
	range_type result{ ::std::ranges::size(range) };
	::std::ranges::transform(NGS_PP_PERFECT_FORWARD(range), result.begin(), [](auto&& value) { return NGS_PP_PERFECT_FORWARD(value); });
	return result;
}

NGS_LIB_MODULE_END