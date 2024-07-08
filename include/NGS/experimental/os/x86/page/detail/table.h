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
		_value.page_base = page.value();
	}
	constexpr auto unbind()
	{
		_value.present = false;
		return physical_address_4_kb(_value.page_base << 12);
	}

	auto page() const { return reinterpret_cast<physical_page_4_kb*>(_value.page_base << 12); }

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

struct table : ::std::ranges::view_interface<table>
{
	NGS_PP_INJECT_EXPLICIT(table, ::std::ranges::view_interface<table>);
public:
	using entry_type = table_entry;

	constexpr auto begin() { return _data.begin(); }
	constexpr auto begin()const { return _data.begin(); }
	constexpr auto end() { return _data.end(); }
	constexpr auto end() const { return _data.end(); }

	using base_type::operator[];
	constexpr auto&& operator[](const page_4_kb* address)
	{
		namespace x86 = ::ngs::os::x86;
		return _data[x86::algorithm::page_table_index<x86::enums::page_size::_4kb>(reinterpret_cast<x86::pointer_underlying_t>(address))];
	}
	constexpr auto&& operator[](const page_4_kb* address) const
	{
		namespace x86 = ::ngs::os::x86;
		return _data[x86::algorithm::page_table_index<x86::enums::page_size::_4kb>(reinterpret_cast<x86::pointer_underlying_t>(address))];
	}

	::std::array<entry_type, ::ngs::bits::literals::operator ""_kb(1)> _data;
};


NGS_LIB_MODULE_END