#pragma once

#include "../bitset.h"
#include "../byte.h"
#include "./bit_of.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

constexpr auto fill() { return ::std::uint8_t{}; }

constexpr auto fill(bitsets::bit_fundamental auto... value)
	requires byte_representable<(sizeof(value) + ...)>
{
	constexpr auto size = (sizeof(value) + ...);
	using result_type = byte<size>;

	return [=]<::std::size_t... Index>(::std::index_sequence<Index...>)
	{
		constexpr auto offsets = layout::offset(NGS_LIB_MODULE_NAME::bit_of<decltype(value)>()...);

		return static_cast<result_type>(((static_cast<result_type>(value) << offsets[Index]) | ...));
	}(::std::make_index_sequence<sizeof...(value)>{});
}

NGS_LIB_MODULE_END