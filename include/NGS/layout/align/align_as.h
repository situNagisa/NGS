#pragma once

#include "./valid_align.h"
#include "./align_of.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

template<align_t Align>
constexpr align_t align_as(::std::span<const align_t> aligns) {

	if constexpr (Align == default_align) {
		return ::std::ranges::max(aligns);
	}
	else if constexpr (Align == no_align) {
		return 1;
	}
	else {
		constexpr align_t a = ::std::ranges::max(aligns);
		return is_valid_align(Align, a) ? Align : a;
	}
}

template<align_t Align>
constexpr align_t align_as(::std::integral auto... aligns) { return NGS_LIB_MODULE_NAME::align_as<Align>(::std::array<align_t, sizeof...(aligns)>{ static_cast<align_t>(aligns)... }); }

template<align_t Align, class... Types>
constexpr align_t align_as() { return NGS_LIB_MODULE_NAME::align_as<Align>(NGS_LIB_MODULE_NAME::align_of<Types>()...); }

NGS_LIB_MODULE_END
