#pragma once

#include "../defined.h"

NGS_LAYOUT_BEGIN

template<size_t _Count>
constexpr size_t align_of(const std::array<size_t, _Count>& aligns) { return std::ranges::max(aligns); }

constexpr size_t align_of(std::integral auto... aligns) { return align_of(std::array{ static_cast<size_t>(aligns)... }); }

template<class _Type>
constexpr size_t align_of() { return alignof(_Type); }

template<class... _Types>
	requires (sizeof...(_Types) > 1)
constexpr size_t align_of() { return align_of(align_of<_Types>()...); }

NGS_LAYOUT_END
