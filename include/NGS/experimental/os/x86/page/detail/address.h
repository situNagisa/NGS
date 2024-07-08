#pragma once

#include "./defined.h"

NGS_LIB_MODULE_BEGIN

template<enums::page_size Size>
struct physical_address;

template<>
struct physical_address<enums::page_size::_4kb>
{
	NGS_PP_INJECT_BEGIN(physical_address);
public:
	constexpr explicit(false) physical_address(::std::uint32_t index) : _address(index) {}
	constexpr auto value() const { return _address; }

	::std::uint32_t _address : 20;
	::std::uint32_t : 12{};
};

template<>
struct physical_address<enums::page_size::_4mb>
{
	NGS_PP_INJECT_BEGIN(physical_address);
public:
	constexpr explicit(false) physical_address(::std::uint32_t index) : _address(index) {}
	constexpr auto value() const { return _address; }

	::std::uint32_t _address : 10;
	::std::uint32_t : 22{};
};

using physical_address_4_kb = physical_address<enums::page_size::_4kb>;
using physical_address_4_mb = physical_address<enums::page_size::_4mb>;

template<enums::page_size Size>
struct address;

template<>
struct address<enums::page_size::_4kb>
{
	NGS_PP_INJECT_BEGIN(address);
public:
	constexpr static auto create_from(::std::uintptr_t address)
	{
		return self_type{
			.directory = static_cast<::std::uint32_t>(address >> 22),
			.table = static_cast<::std::uint32_t>((address >> 12) & 0x3ff),
			.offset = static_cast<::std::uint32_t>(address & 0xfff),
		};
	}
	constexpr static auto create_from(const void* ptr)
	{
		return create_from(::std::bit_cast<::std::uintptr_t>(ptr));
	}

	::std::uint32_t directory : 10;
	::std::uint32_t table : 10;
	::std::uint32_t offset : 12;
};

template<>
struct address<enums::page_size::_4mb>
{
	NGS_PP_INJECT_BEGIN(address);
public:
	constexpr static auto create_from(::std::uintptr_t address)
	{
		return self_type{
			.directory = static_cast<::std::uint32_t>(address >> 22),
			.offset = static_cast<::std::uint32_t>(address & 0x3fffff),
		};
	}
	constexpr static auto create_from(const void* ptr)
	{
		return create_from(::std::bit_cast<::std::uintptr_t>(ptr));
	}

	::std::uint32_t directory : 10;
	::std::uint32_t offset : 22;
};

using address_4_kb = address<enums::page_size::_4kb>;
using address_4_mb = address<enums::page_size::_4mb>;

NGS_LIB_MODULE_END