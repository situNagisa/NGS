#pragma once

#include "./align.h"
#include "./offset.h"
#include "./defined.h"

NGS_LIB_BEGIN

template<::std::size_t Align, ::std::size_t Count> requires (aligns::is_valid_align(aligns::align_t(Align)))
constexpr auto structure(const ::std::array<::std::size_t, Count>& sizes) {
	using result_type = ::std::array<::std::pair<::std::size_t,::std::size_t>, Count>;
	auto offsets = NGS_LIB_NAME::offset<Align, Count>(sizes);

	result_type result{};

	for(::std::size_t i = 0; i < result.size(); i++)
	{
		result[i] = { sizes[i], offsets[i] };
	}
	return result;
}

template<::std::size_t Align = 1> requires (aligns::is_valid_align(aligns::align_t(Align)))
constexpr auto structure(::std::integral auto... sizes) {
	return NGS_LIB_NAME::structure<Align>(::std::array{ static_cast<size_t>(sizes)... });
}

NGS_LIB_END