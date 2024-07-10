#pragma once

#include "./address.h"
#include "./page.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

struct table_entry
{
	NGS_PP_INJECT_BEGIN(table_entry);
public:
	using table_type = registers::bit32::page_table_entry;

	constexpr explicit(false) table_entry(const table_type& value = {}) : _value(value) {}

	constexpr bool present() const { return _value.present; }

	constexpr void bind(physical_address_4_kb page)
	{
		_value.present = true;
		_value.page_base = page.base();
	}
	constexpr auto unbind()
	{
		_value.present = false;
		return physical_address_4_kb(_value.page_base << 12);
	}

	constexpr auto access_type() const { return static_cast<enums::access_type>(_value.access_type); }
	constexpr void set_access_type(enums::access_type value) { _value.access_type = static_cast<table_type::underlying_type>(value); }

	constexpr auto privilege() const { return static_cast<enums::page_privilege>(_value.user_supervisor); }
	constexpr void set_privilege(enums::page_privilege privilege) { _value.user_supervisor = static_cast<table_type::underlying_type>(privilege); }

	constexpr bool page_level_write_through() const { return _value.page_level_write_through; }
	constexpr bool page_level_cache_disable() const { return _value.page_level_cache_disable; }
	constexpr bool accessed() const { return _value.accessed; }
	constexpr bool dirty() const { return _value.dirty; }
	constexpr bool pat() const { return _value.pat; }
	constexpr bool global() const { return _value.global; }

	table_type _value;
};


auto as_table (page_4_kb& page)
{
	return ::std::span<table_entry, page_4_kb::page_size / sizeof(table_entry)>(page);
}

auto as_table(const page_4_kb& page)
{
	return ::std::span<const table_entry, page_4_kb::page_size / sizeof(table_entry)>(page);
}

NGS_LIB_MODULE_END