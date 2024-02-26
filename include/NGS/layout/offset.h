#pragma once

#include "./align.h"
#include "./defined.h"

NGS_LIB_BEGIN

template<::std::size_t Align,::std::size_t Count> requires (aligns::is_valid_align(aligns::align_t(Align)))
constexpr auto offset(const ::std::array<::std::size_t, Count>& sizes) {
	using result_type = std::array<::std::size_t, Count>;
	result_type offsets{};

	if constexpr (Align == 1) {
		for (::std::size_t i = 1; i < offsets.size(); i++)
		{
			offsets[i] = offsets[i - 1] + sizes[i - 1];
		}
	}
	else {
		for (size_t i = 1; i < offsets.size(); i++)
		{
			auto start = offsets[i - 1] + sizes[i - 1];
			auto align_size = (sizes[i] > Align ? Align : sizes[i]);
			auto model = start % align_size;
			if (!model) {
				offsets[i] = start;
				continue;
			}

			offsets[i] = start + align_size - model;
		}
	}
	return offsets;
}

template<::std::size_t Align> requires (aligns::is_valid_align(aligns::align_t(Align)))
constexpr auto offset(::std::integral auto... sizes) {
	return layout::offset<Align>(::std::array{ static_cast<size_t>(sizes)... });
}

NGS_LIB_END
