#pragma once

#include "../defined.h"
#include "NGS/layout/align/constant.h"
#include "NGS/layout/offset.h"

NGS_LAYOUT_BEGIN

template<size_t _Align = no_align, size_t _Count>
constexpr size_t size_of(const std::array<size_t, _Count>& sizes) {
	auto offsets = layout::offset<_Align>(sizes);
	const size_t size = offsets[offsets.size() - 1] + sizes[sizes.size() - 1];

	const auto model = size % _Align;
	if (!model) return size;
	return size + _Align - model;
}

template<size_t _Align = no_align>
constexpr size_t size_of(std::integral auto... sizes) { return layout::size_of<_Align>(std::array{ static_cast<size_t>(sizes)... }); }

template<class _Type>
constexpr size_t size_of() { return sizeof(_Type); }

template<class... _Types>
	requires (sizeof...(_Types) > 1)
constexpr size_t size_of() { return layout::size_of(size_of<_Types>()...); }

template<size_t _Align, class... _Types>
	requires (sizeof...(_Types) > 1)
constexpr size_t size_of() { return layout::size_of< _Align >(size_of<_Types>()...); }

NGS_LAYOUT_END
