#pragma once

#include "../fieldset.h"
#include "./type.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

struct descriptor
{
	NGS_MPL_ENVIRON_BEGIN(descriptor);
public:
	using underlying_type = ::std::uint64_t;

	enum class descriptor_type : underlying_type
	{
		system = 0,
		code_data = 1
	};

	enum class operation_size : underlying_type
	{
		bits16 = 0,
		bits32 = 1
	};

	enum class limit_granularity : underlying_type
	{
		bit = 0,
		page = 1
	};

	enum class descriptor_mode : underlying_type
	{
		compatibility = 0,
		long_mode = 1
	};

	constexpr static self_type create(underlying_type value)
	{
		if (::std::is_constant_evaluated())
		{
			return {
				.limit_low = static_cast<underlying_type>((value >> 0) & 0xFFFF),
				.base_low = static_cast<underlying_type>((value >> 16) & 0xFFFF),
				.base_middle = static_cast<underlying_type>((value >> 32) & 0xFF),
				.type = static_cast<underlying_type>((value >> 40) & 0xF),
				.s = static_cast<enum descriptor_type>((value >> 44) & 0x1),
				.dpl = static_cast<underlying_type>((value >> 45) & 0x3),
				.p = static_cast<underlying_type>((value >> 47) & 0x1),
				.limit_high = static_cast<underlying_type>((value >> 48) & 0xF),
				.avl = static_cast<underlying_type>((value >> 52) & 0x1),
				.l = static_cast<enum descriptor_mode>((value >> 53) & 0x1),
				.db = static_cast<enum operation_size>((value >> 54) & 0x1),
				.g = static_cast<limit_granularity>((value >> 55) & 0x1),
				.base_high = static_cast<underlying_type>((value >> 56) & 0xFF),
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
			return (static_cast<underlying_type>(limit_low) << 0) |
				(static_cast<underlying_type>(base_low) << 16) |
				(static_cast<underlying_type>(base_middle) << 32) |
				(static_cast<underlying_type>(type) << 40) |
				(static_cast<underlying_type>(s) << 44) |
				(static_cast<underlying_type>(dpl) << 45) |
				(static_cast<underlying_type>(p) << 47) |
				(static_cast<underlying_type>(limit_high) << 48) |
				(static_cast<underlying_type>(avl) << 52) |
				(static_cast<underlying_type>(l) << 53) |
				(static_cast<underlying_type>(db) << 54) |
				(static_cast<underlying_type>(g) << 55) |
				(static_cast<underlying_type>(base_high) << 56);
		}
		else
		{
			return *reinterpret_cast<const underlying_type*>(this);
		}
	}

	underlying_type limit_low : 16;
	underlying_type base_low : 16;

	underlying_type base_middle : 8;

	underlying_type type : 4;
	descriptor_type s : 1;
	underlying_type dpl : 2;
	underlying_type p : 1;

	underlying_type limit_high : 4;
	underlying_type avl : 1;
	descriptor_mode l : 1;
	operation_size db : 1;
	limit_granularity g : 1;

	underlying_type base_high : 8;

	[[nodiscard]] constexpr ::std::uint32_t base() const { return (static_cast<::std::uint32_t>(base_high) << 24) | (static_cast<::std::uint32_t>(base_middle) << 16) | base_low; }
	[[nodiscard]] constexpr ::std::uint32_t limit() const { return (static_cast<::std::uint32_t>(limit_high) << 16) | limit_low; }
	[[nodiscard]] constexpr auto segment() const { return segment_info::create(static_cast<segment_info::underlying_type>(type)); }
	[[nodiscard]] constexpr auto descriptor_type() const { return s; }
	[[nodiscard]] constexpr auto privilege_level() const { return dpl; }
	[[nodiscard]] constexpr bool present() const { return p; }
	[[nodiscard]] constexpr auto available() const { return avl; }
	[[nodiscard]] constexpr auto mode() const { return l; }
	[[nodiscard]] constexpr auto operation_size() const { return db; }
	[[nodiscard]] constexpr auto granularity() const { return g; }

	constexpr void load() { p = 1; }
	constexpr void unload() { p = 0; }
};

struct descriptor_wrapper : fieldsets::wrapper<descriptor>
{
	NGS_MPL_ENVIRON(descriptor_wrapper);
public:
	using base_type::base_type;
	using base_type::operator=;

	constexpr descriptor_wrapper(
		underlying_type base,
		underlying_type limit,
		segment_info segment,
		enum descriptor::descriptor_type descriptor_type,
		underlying_type privilege_level,
		bool present,
		underlying_type available,
		enum descriptor::descriptor_mode mode,
		enum descriptor::operation_size operation_size,
		enum descriptor::limit_granularity granularity
	)
		: base_type({
			.limit_low = static_cast<underlying_type>((limit >> 0) & 0xFFFF),
			.base_low = static_cast<underlying_type>((base >> 0) & 0xFFFF),
			.base_middle = static_cast<underlying_type>((base >> 16) & 0xFF),
			.type = static_cast<underlying_type>(segment),
			.s = (descriptor_type),
			.dpl = static_cast<underlying_type>(privilege_level),
			.p = static_cast<underlying_type>(present),
			.limit_high = static_cast<underlying_type>((limit >> 16) & 0xF),
			.avl = static_cast<underlying_type>(available),
			.l = (mode),
			.db = (operation_size),
			.g = (granularity),
			.base_high = static_cast<underlying_type>((base >> 24) & 0xFF),
		})
	{}
};

NGS_LIB_MODULE_END