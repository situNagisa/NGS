#pragma once

#include "./concept.h"
#include "./constant.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

constexpr auto align_of(const ::std::ranges::input_range auto& aligns) requires align<::std::ranges::range_value_t<decltype(aligns)>>
{
	return ::std::ranges::max(aligns, [](const auto& left, const auto& right) { return left < right; });
}

constexpr decltype(auto) align_of(::std::integral auto... aligns)
{
	return NGS_LIB_MODULE_NAME::align_of(::std::array{ static_cast<align_t>(aligns)... });
}

constexpr decltype(auto) align_of(align auto... aligns)
{
	return NGS_LIB_MODULE_NAME::align_of(::std::array{ static_cast<align_t>(aligns)... });
}

template<class Type>
constexpr align_t align_of() { return alignof(Type); }

template<class... Types>
	requires (sizeof...(Types) > 1)
constexpr decltype(auto) align_of()
{
	return NGS_LIB_MODULE_NAME::align_of(NGS_LIB_MODULE_NAME::align_of<Types>()...);
}

NGS_LIB_MODULE_END
