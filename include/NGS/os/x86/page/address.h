#pragma once

#include "../granularity.h"
#include "../pointer.h"
#include "../space.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

template<granularity>
inline constexpr ::std::size_t directory_selector_bit_width = 0;

template<>
inline constexpr ::std::size_t directory_selector_bit_width<granularity::bit> = 10;

template<>
inline constexpr ::std::size_t directory_selector_bit_width<granularity::page> = 10;

template<granularity>
inline constexpr ::std::size_t table_selector_bit_width = 0;

template<>
inline constexpr ::std::size_t table_selector_bit_width<granularity::bit> = 10;

template<>
inline constexpr ::std::size_t table_selector_bit_width<granularity::page> = 0;

template<granularity G>
inline constexpr ::std::size_t page_offset_bit_width = bits::algorithm::bit_of<pointer_t>() - directory_selector_bit_width<G> - table_selector_bit_width<G>;

template<granularity G>
constexpr ::std::size_t page_directory_index(spaces::visual_address visual)
{
	return bits::algorithm::span_value(visual.value(), table_selector_bit_width<G> + page_offset_bit_width<G>, directory_selector_bit_width<G>);
}

template<granularity G>
constexpr ::std::size_t page_table_index(spaces::visual_address visual)
{
	return bits::algorithm::span_value(visual.value(), page_offset_bit_width<G>, table_selector_bit_width<G>);
}

template<granularity G>
constexpr ::std::size_t page_offset(spaces::visual_address visual)
{
	return bits::algorithm::span_value(visual.value(), 0, page_offset_bit_width<G>);
}

template<granularity G>
constexpr auto page_base(spaces::physical_address physical)
{
	return bits::algorithm::span_value(physical.value(), page_offset_bit_width<G>, bits::algorithm::bit_of<pointer_t>() - page_offset_bit_width<G>);
}

NGS_LIB_MODULE_END