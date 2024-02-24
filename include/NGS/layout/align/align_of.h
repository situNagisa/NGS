#pragma once

#include "./defined.h"

NGS_LIB_MODULE_BEGIN

constexpr align_t align_of(::std::span<align_t> aligns) { return ::std::ranges::max(aligns); }

constexpr align_t align_of(::std::integral auto... aligns) { return NGS_LIB_MODULE_NAME::align_of(::std::array{ static_cast<align_t>(aligns)... }); }

template<class Type>
constexpr align_t align_of() { return alignof(Type); }

template<class... Types>
	requires (sizeof...(Types) > 1)
constexpr align_t align_of() { return NGS_LIB_MODULE_NAME::align_of(NGS_LIB_MODULE_NAME::align_of<Types>()...); }

NGS_LIB_MODULE_END
