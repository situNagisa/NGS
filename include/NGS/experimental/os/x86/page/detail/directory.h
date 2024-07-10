#pragma once

#include "./page.h"
#include "./table.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

struct directory_entry
{
	NGS_PP_INJECT_BEGIN(directory_entry);
public:
	using directory_type = registers::bit32::page_directory_entry_4kb;

	constexpr explicit(false) directory_entry(const directory_type& value = {}) : _value(value) {}

	constexpr bool present() const { return _value.present; }

	void bind(physical_address_4_kb address)
	{
		_value.present = true;
		_value.table_base = address.base();
	}

	auto unbind()
	{
		_value.present = false;
		return physical_address_4_kb(_value.table_base << 12);
	}

	constexpr auto access_type() const { return static_cast<enums::access_type>(_value.access_type); }
	constexpr void set_access_type(enums::access_type value) { _value.access_type = static_cast<directory_type::underlying_type>(value); }

	constexpr bool privilege() const { return _value.user_supervisor; }
	constexpr void set_privilege(enums::page_privilege privilege) { _value.user_supervisor = static_cast<directory_type::underlying_type>(privilege); }

	constexpr bool page_level_write_through() const { return _value.page_level_write_through; }
	constexpr bool page_level_cache_disable() const { return _value.page_level_cache_disable; }
	constexpr bool accessed() const { return _value.accessed; }
	constexpr bool dirty() const { return _value.dirty; }
	constexpr auto page_size() const { return static_cast<enums::page_size>(_value.page_size); }

	directory_type _value;
};


auto as_directory(page_4_kb& page)
{
	return ::std::span<directory_entry, page_4_kb::page_size / sizeof(directory_entry)>(page);
}

auto as_directory(const page_4_kb& page)
{
	return ::std::span<const directory_entry, page_4_kb::page_size / sizeof(directory_entry)>(page);
}

NGS_LIB_MODULE_END