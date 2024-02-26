#pragma once

#include "../defined.h"
#include "../offset.h"

NGS_LIB_BEGIN

template<::std::size_t Align = no_align.align(), ::std::size_t Count>
constexpr ::std::size_t size_of(const std::array<::std::size_t, Count>& sizes) {
	auto offsets = layout::offset<Align>(sizes);
	const ::std::size_t size = offsets[offsets.size() - 1] + sizes[sizes.size() - 1];

	const auto model = size % Align;
	if (!model) return size;
	return size + Align - model;
}

template<::std::size_t Align = no_align.align()>
constexpr ::std::size_t size_of(std::integral auto... sizes) { return layout::size_of<Align>(std::array{ static_cast<::std::size_t>(sizes)... }); }

template<class Type>
constexpr ::std::size_t size_of() { return sizeof(Type); }

template<class... Types>
	requires (sizeof...(Types) > 1)
constexpr ::std::size_t size_of() { return layout::size_of(size_of<Types>()...); }

template<::std::size_t Align = no_align.align(), class... Types>
	requires (sizeof...(Types) > 1)
constexpr ::std::size_t size_of() { return layout::size_of< Align >(size_of<Types>()...); }

NGS_LIB_END
