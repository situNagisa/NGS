#pragma once

#include "./defined.h"

NGS_LIB_MODULE_BEGIN

using address_t = ::std::uint32_t;

template<::std::size_t OffsetSize>
struct basic_physical_address
{
	NGS_PP_INJECT_BEGIN(basic_physical_address);
public:
	constexpr static auto offset_size = OffsetSize;
	constexpr static auto base_size = bits::algorithm::bit_of<address_t>() - offset_size;

	constexpr explicit(false) basic_physical_address(address_t address) : _address(address >> 12) {}
	constexpr auto base() const { return _address; }
	constexpr auto address() const { return _address << offset_size; }

	address_t _address : base_size;
	address_t : offset_size;
};

template<enums::page_size Size>
using physical_address = basic_physical_address<::std::bit_width(enums::factor(Size) - 1)>;

using physical_address_4_kb = physical_address<enums::page_size::_4kb>;
using physical_address_4_mb = physical_address<enums::page_size::_4mb>;

template<enums::page_size Size>
struct address;

template<>
struct address<enums::page_size::_4kb>
{
	NGS_PP_INJECT_BEGIN(address);
public:
	constexpr address() = default;
	constexpr explicit(true) address(::std::uintptr_t address)
		: directory(static_cast<::std::uint32_t>(address >> 22))
		, table(static_cast<::std::uint32_t>((address >> 12) & 0x3ff))
		, offset(static_cast<::std::uint32_t>(address & 0xfff))
	{}

	constexpr explicit(false) address(const void* ptr)
		: self_type(::std::bit_cast<::std::uintptr_t>(ptr))
	{}

	::std::uint32_t directory : 10;
	::std::uint32_t table : 10;
	::std::uint32_t offset : 12;
};

template<>
struct address<enums::page_size::_4mb>
{
	NGS_PP_INJECT_BEGIN(address);
public:
	constexpr address() = default;
	constexpr explicit(true) address(::std::uintptr_t address)
		: directory(static_cast<::std::uint32_t>(address >> 22))
		, offset(static_cast<::std::uint32_t>(address & 0x3fffff))
	{}

	constexpr explicit(false) address(const void* ptr)
		: self_type(::std::bit_cast<::std::uintptr_t>(ptr))
	{}

	::std::uint32_t directory : 10;
	::std::uint32_t offset : 22;
};

using address_4_kb = address<enums::page_size::_4kb>;
using address_4_mb = address<enums::page_size::_4mb>;

NGS_LIB_MODULE_END