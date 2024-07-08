#pragma once

#include "./register.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

struct global_descriptor_table_register
{
	NGS_PP_INJECT_BEGIN(global_descriptor_table_register);
public:
	using underlying_type = ::std::uint64_t;
	using register_category_type = tags::gdtr;

	::std::uint16_t size;
	::std::uint16_t address_low;
	::std::uint16_t address_high;

	constexpr ::std::uintptr_t address() const noexcept
	{
		return bits::algorithm::fill(address_low, address_high);
	}
};

struct local_descriptor_table_register
{
	NGS_PP_INJECT_BEGIN(local_descriptor_table_register);
public:
	using underlying_type = ::std::uint16_t;
	using register_category_type = tags::ldtr;

	underlying_type rpl : 2;
	underlying_type ti : 1;
	underlying_type index : 13;
};

struct interrupt_descriptor_table_register
{
	NGS_PP_INJECT_BEGIN(interrupt_descriptor_table_register);
public:
	using underlying_type = ::std::uint64_t;
	using register_category_type = tags::idtr;

	::std::uint16_t size;
	::std::uint16_t address_low;
	::std::uint16_t address_high;

	constexpr ::std::uintptr_t address() const noexcept
	{
		return bits::algorithm::fill(address_low, address_high);
	}
};

NGS_LIB_MODULE_END
