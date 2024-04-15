#pragma once

#include "./defined.h"

NGS_LIB_MODULE_BEGIN

struct visual_address_4_kb
{
	NGS_MPL_ENVIRON_BEGIN(visual_address_4_kb);
public:
	using underlying_type = ::std::uint32_t;

	constexpr static self_type create(underlying_type value)
	{
		if (::std::is_constant_evaluated())
		{
			return {
				.address = static_cast<underlying_type>((value >> 0) & bits::mask(page_address_bit_size)),
				.page_table_index = static_cast<underlying_type>((value >> page_address_bit_size) & bits::mask(page_table_bit_size)),
				.page_directory_index =static_cast<underlying_type>((value >> (page_address_bit_size + page_table_bit_size)) & bits::mask(page_directory_bit_size))
			};
		}
		else
		{
			return *reinterpret_cast<self_type*>(&value);
		}
	}

	constexpr explicit(false) operator underlying_type()const
	{
		if (::std::is_constant_evaluated())
		{
			return (address << 0) | (page_table_index << page_address_bit_size) | (page_directory_index << (page_address_bit_size + page_table_bit_size));
		}
		else
		{
			return *reinterpret_cast<const underlying_type*>(this);
		}
	}

	constexpr static ::std::size_t address_bit_size = bits::as_bit<::std::uint32_t>();
	constexpr static ::std::size_t page_directory_bit_size = 10;
	constexpr static ::std::size_t page_table_bit_size = 10;
	constexpr static ::std::size_t page_address_bit_size = address_bit_size - page_directory_bit_size - page_table_bit_size;

	underlying_type address : page_address_bit_size;
	underlying_type page_table_index : page_table_bit_size;
	underlying_type page_directory_index : page_directory_bit_size;
};

struct visual_address_4_mb
{
	NGS_MPL_ENVIRON_BEGIN(visual_address_4_mb);
public:
	using underlying_type = ::std::uint32_t;

	constexpr static self_type create(underlying_type value)
	{
		if (::std::is_constant_evaluated())
		{
			return {
				.address = static_cast<underlying_type>((value >> 0) & bits::mask(page_address_bit_size)),
				.page_directory_index = static_cast<underlying_type>((value >> page_address_bit_size) & bits::mask(page_directory_bit_size))
			};
		}
		else
		{
			return *reinterpret_cast<self_type*>(&value);
		}
	}

	constexpr explicit(false) operator underlying_type()const
	{
		if (::std::is_constant_evaluated())
		{
			return (address << 0) | (page_directory_index << page_address_bit_size);
		}
		else
		{
			return *reinterpret_cast<const underlying_type*>(this);
		}
	}

	constexpr static ::std::size_t address_bit_size = bits::as_bit<::std::uint32_t>();
	constexpr static ::std::size_t page_directory_bit_size = 10;
	constexpr static ::std::size_t page_address_bit_size = address_bit_size - page_directory_bit_size;

	underlying_type address : page_address_bit_size;
	underlying_type page_directory_index : page_directory_bit_size;
};

NGS_LIB_MODULE_END