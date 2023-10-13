#pragma once

#include "./is_align.h"
#include "./align_of.h"

NGS_LAYOUT_BEGIN

template<size_t _Align, size_t _Count>
constexpr size_t align_as(const std::array<size_t, _Count>& aligns) {

	if constexpr (_Align == default_align) {
		return std::ranges::max(aligns);
	}
	else if constexpr (_Align == no_align) {
		return 1;
	}
	else {
		constexpr size_t a = std::ranges::max(aligns);
		return is_align(_Align, a) ? _Align : a;
	}
}
template<size_t _Align>
constexpr size_t align_as(std::integral auto... aligns) { return align_as<_Align>(std::array{ static_cast<size_t>(aligns)... }); }

template<size_t _Align, class... _Types>
constexpr size_t align_as() { return align_as<_Align>(align_of<_Types>()...); }

NGS_LAYOUT_END
