#pragma once

#include "./defined.h"

NGS_LIB_MODULE_BEGIN

enum class privilege : ::std::uint32_t
{
	supervisor,
	user,
};
enum class page_size : ::std::uint32_t
{
	_4kb,
	_4mb,
};

struct page_directory_entry
{
	::std::uint32_t p : 1;
	::std::uint32_t rw : 1;
	privilege us : 1;
	::std::uint32_t pwt : 1;
	::std::uint32_t pcd : 1;
	::std::uint32_t a : 1;
	::std::uint32_t d : 1;
	page_size ps : 1;

	::std::uint32_t g : 1;
	::std::uint32_t avl : 3;

	::std::uint32_t base : 20;

	[[nodiscard]] constexpr bool present() const { return p; }
	[[nodiscard]] constexpr bool readable() const { return true; }
	[[nodiscard]] constexpr bool writable() const { return rw; }
	[[nodiscard]] constexpr auto privilege() const { return us; }
	[[nodiscard]] constexpr auto page_level_write_through() const { return pwt; }
	[[nodiscard]] constexpr bool page_level_cache_disable() const { return pcd; }
	[[nodiscard]] constexpr bool accessed()const { return a; }
	[[nodiscard]] constexpr bool dirty() const { return d; }
	[[nodiscard]] constexpr auto page_size() const { return ps; }
	[[nodiscard]] constexpr bool global() const { return g; }
	[[nodiscard]] constexpr auto available()const { return avl; }
	[[nodiscard]] constexpr auto page_base_address()const { return base; }

	constexpr void load() { p = true; }
	constexpr void unload() { p = false; }

	constexpr void enable_write() { rw = true; }
	constexpr void disable_write() { rw = false; }

	constexpr void set_privilege(enum privilege value) { us = value; }

	constexpr void page_resize(enum page_size value) { ps = value; }
};

constexpr auto make_page_directory_entry(
	::std::uint32_t page_base_address,
	bool is_present,
	bool is_writable,
	enum privilege privilege,
	enum page_size page_size
){
	return page_directory_entry
	{
		.p = is_present,
		.rw = is_writable,
		.us = privilege,
		.ps = page_size,
		.base = page_base_address,
	};	
}

NGS_LIB_MODULE_END