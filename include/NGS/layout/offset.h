#pragma once

#include "./align.h"

NGS_LAYOUT_BEGIN

template<size_t _Align,size_t _Count>
	requires CAlign<ccpt::uint_<_Align>>
constexpr auto offset(const std::array<size_t,_Count>& sizes){
	using result_type = std::array<size_t, _Count>;
	result_type offsets{};
	if constexpr(_Align == no_align) {
		for (size_t i = 1; i < offsets.size(); i++)
		{
			offsets[i] = offsets[i - 1] + sizes[i - 1];
		}
	}
	else if constexpr (_Align == default_align) {
		static_assert(_Align == default_align, "invalid align");
	}
	else {
		for (size_t i = 1; i < offsets.size(); i++)
		{
			auto start = offsets[i - 1] + sizes[i - 1];
			auto align_size = (sizes[i] > _Align ? _Align : sizes[i]);
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

template<size_t _Align>
	requires CAlign<ccpt::uint_<_Align>>
constexpr auto offset(std::integral auto... sizes) {
	return offset<_Align>(std::array{ static_cast<size_t>(sizes)... });
}

NGS_LAYOUT_END
