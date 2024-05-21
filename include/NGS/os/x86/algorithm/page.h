#pragma once

#include "../pointer.h"
#include "../enum.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

template<enums::page_size>
inline constexpr ::std::size_t directory_selector_bit_width = 0;

template<>
inline constexpr ::std::size_t directory_selector_bit_width<enums::page_size::_4kb> = 10;

template<>
inline constexpr ::std::size_t directory_selector_bit_width<enums::page_size::_4mb> = 10;

template<enums::page_size>
inline constexpr ::std::size_t table_selector_bit_width = 0;

template<>
inline constexpr ::std::size_t table_selector_bit_width<enums::page_size::_4kb> = 10;

template<>
inline constexpr ::std::size_t table_selector_bit_width<enums::page_size::_4mb> = 0;

template<enums::page_size S>
inline constexpr ::std::size_t page_offset_bit_width = bits::algorithm::bit_of<pointer_underlying_t>() - directory_selector_bit_width<S> - table_selector_bit_width<S>;

template<enums::page_size S>
constexpr ::std::size_t page_directory_index(pointer_underlying_t visual)
{
	return bits::algorithm::extract(visual, table_selector_bit_width<S> + page_offset_bit_width<S>, directory_selector_bit_width<S>);
}

template<enums::page_size S>
constexpr ::std::size_t page_table_index(pointer_underlying_t visual)
{
	return bits::algorithm::extract(visual, page_offset_bit_width<S>, table_selector_bit_width<S>);
}

template<enums::page_size S>
constexpr ::std::size_t page_offset(pointer_underlying_t visual)
{
	return bits::algorithm::extract(visual, 0, page_offset_bit_width<S>);
}

template<enums::page_size S>
constexpr auto page_base(pointer_underlying_t physical)
{
	return bits::algorithm::extract(physical, page_offset_bit_width<S>, bits::algorithm::bit_of<pointer_underlying_t>() - page_offset_bit_width<S>);
}

NGS_LIB_MODULE_END