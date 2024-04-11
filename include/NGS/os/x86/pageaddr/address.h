#pragma once

#include "./defined.h"

NGS_LIB_MODULE_BEGIN

struct visual_address_4_kb
{
	constexpr static ::std::size_t address_bit_size = bits::as_bit<::std::uint32_t>();
	constexpr static ::std::size_t page_directory_bit_size = 10;
	constexpr static ::std::size_t page_table_bit_size = 10;
	constexpr static ::std::size_t page_address_bit_size = address_bit_size - page_directory_bit_size - page_table_bit_size;

	::std::uint32_t address : page_address_bit_size;
	::std::uint32_t page_table_index : page_table_bit_size;
	::std::uint32_t page_directory_index : page_directory_bit_size;

	constexpr visual_address_4_kb() = default;
	constexpr visual_address_4_kb(::std::uint32_t address, ::std::uint32_t page_table_index, ::std::uint32_t page_directory_index)
		: address(address)
		, page_table_index(page_table_index)
		, page_directory_index(page_directory_index)
	{}
	constexpr explicit(false) visual_address_4_kb(::std::uint32_t address)
		: address(static_cast<::std::uint32_t>((address >> 0) & bits::mask(page_address_bit_size)))
		, page_table_index(static_cast<::std::uint32_t>((address >> page_address_bit_size) & bits::mask(page_table_bit_size)))
		, page_directory_index(static_cast<::std::uint32_t>((address >> (page_address_bit_size + page_table_bit_size)) & bits::mask(page_directory_bit_size)))
	{}

	constexpr auto value()const { return (address << 0) | (page_table_index << page_address_bit_size) | (page_directory_index << (page_address_bit_size + page_table_bit_size)); }
};

struct visual_address_4_mb
{
	constexpr static ::std::size_t address_bit_size = bits::as_bit<::std::uint32_t>();
	constexpr static ::std::size_t page_directory_bit_size = 10;
	constexpr static ::std::size_t page_address_bit_size = address_bit_size - page_directory_bit_size;

	::std::uint32_t address : page_address_bit_size;
	::std::uint32_t page_directory_index : page_directory_bit_size;

	constexpr visual_address_4_mb() = default;
	constexpr visual_address_4_mb(::std::uint32_t address, ::std::uint32_t page_directory_index)
		: address(address)
		, page_directory_index(page_directory_index)
	{}
	constexpr explicit(false) visual_address_4_mb(::std::uint32_t address)
		: address(static_cast<::std::uint32_t>((address >> 0) & bits::mask(page_address_bit_size)))
		, page_directory_index(static_cast<::std::uint32_t>((address >> page_address_bit_size) & bits::mask(page_directory_bit_size)))
	{}

	constexpr auto value()const { return (address << 0) | (page_directory_index << page_address_bit_size); }
};

NGS_LIB_MODULE_END