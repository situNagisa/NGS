#pragma once

#include "../granularity.h"
#include "../pointer.h"
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
inline constexpr ::std::size_t page_address_bit_width = bits::algorithm::bit_of<pointer_t>() - directory_selector_bit_width<G> - table_selector_bit_width<G>;

template<granularity G>
constexpr ::std::size_t page_directory_index(pointer_t value)
{
	return bits::algorithm::span_value(value, table_selector_bit_width<G> + page_address_bit_width<G>, directory_selector_bit_width<G>);
}

template<granularity G>
constexpr ::std::size_t page_table_index(pointer_t value)
{
	return bits::algorithm::span_value(value, page_address_bit_width<G>, table_selector_bit_width<G>);
}

template<granularity G>
constexpr ::std::size_t page_offset(pointer_t value)
{
	return bits::algorithm::span_value(value, 0, page_address_bit_width<G>);
}

NGS_LIB_MODULE_END