#pragma once

#include "../fieldset.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN


struct directory_entry
{
	NGS_MPL_ENVIRON_BEGIN(directory_entry);
public:
	using underlying_type = ::std::uint32_t;


	enum class privilege : underlying_type
	{
		supervisor,
		user,
	};
	enum class page_size : underlying_type
	{
		_4kb,
		_4mb,
	};

	constexpr static self_type create(underlying_type value)
	{
		if (::std::is_constant_evaluated())
		{
			return {
				.p = static_cast<underlying_type>((value >> 0)),
				.rw = static_cast<underlying_type>((value >> 1)),
				.us = static_cast<enum privilege>((value >> 2)),
				.pwt = static_cast<underlying_type>((value >> 3)),
				.pcd = static_cast<underlying_type>((value >> 4)),
				.a = static_cast<underlying_type>((value >> 5)),
				.d = static_cast<underlying_type>((value >> 6)),
				.ps = static_cast<enum page_size>((value >> 7)),
				.g = static_cast<underlying_type>((value >> 8)),
				.avl = static_cast<underlying_type>((value >> 9)),
				.base = static_cast<underlying_type>((value >> 12)),
			};
		}
		else
		{
			return *reinterpret_cast<self_type*>(&value);
		}
	}

	constexpr explicit(false) operator underlying_type() const
	{
		if (::std::is_constant_evaluated())
			{
			return
				(p << 0) |
				(rw << 1) |
				(static_cast<underlying_type>(us) << 2) |
				(pwt << 3) |
				(pcd << 4) |
				(a << 5) |
				(d << 6) |
				(static_cast<underlying_type>(ps) << 7) |
				(g << 8) |
				(avl << 9) |
				(base << 12);
		}
		else
		{
			return *reinterpret_cast<const underlying_type*>(this);
		}
	}

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

struct directory_entry_wrapper : fieldsets::wrapper<directory_entry>
{
	NGS_MPL_ENVIRON(directory_entry_wrapper);
public:

	using base_type::underlying_type;

	using base_type::base_type;
	using base_type::operator=;

	constexpr directory_entry_wrapper(
		::std::uint32_t base_address,
		bool present,
		bool writable,
		enum directory_entry::privilege privilege,
		bool page_level_write_through,
		bool page_level_cache_disable,
		bool accessed,
		bool dirty,
		enum directory_entry::page_size page_size,
		bool global,
		::std::uint32_t available
	)
		: base_type({
				.p = present,
				.rw = writable,
				.us = privilege,
				.pwt = page_level_write_through,
				.pcd = page_level_cache_disable,
				.a = accessed,
				.d = dirty,
				.ps = page_size,
				.g = global,
				.avl = available,
				.base = base_address
			})
	{}
};

NGS_LIB_MODULE_END