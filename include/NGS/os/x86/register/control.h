#pragma once

#include "./defined.h"

NGS_LIB_MODULE_BEGIN

struct control0
{
	NGS_MPL_ENVIRON_BEGIN(control0);
public:
	using underlying_type = ::std::uint32_t;

	constexpr static self_type create(underlying_type value)
	{
		if (::std::is_constant_evaluated())
		{
			return {
			.pe = static_cast<underlying_type>(value >> 0),
			.mp = static_cast<underlying_type>(value >> 1),
			.em = static_cast<underlying_type>(value >> 2),
			.ts = static_cast<underlying_type>(value >> 3),
			.et = static_cast<underlying_type>(value >> 4),
			.ne = static_cast<underlying_type>(value >> 5),
			.wp = static_cast<underlying_type>(value >> 16),
			.am = static_cast<underlying_type>(value >> 18),
			.nw = static_cast<underlying_type>(value >> 29),
			.cd = static_cast<underlying_type>(value >> 30),
			.pg = static_cast<underlying_type>(value >> 31),
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
			return (pe << 0) | (mp << 1) | (em << 2) | (ts << 3) | (et << 4) | (ne << 5) | (wp << 16) | (am << 18) | (nw << 29) | (cd << 30) | (pg << 31);
		}
		else
		{
			return *reinterpret_cast<const underlying_type*>(this);
		}
	}

	underlying_type pe : 1;
	underlying_type mp : 1;
	underlying_type em : 1;
	underlying_type ts : 1;
	underlying_type et : 1;
	underlying_type ne : 1;

	underlying_type : 10;

	underlying_type wp : 1;

	underlying_type : 1;

	underlying_type am : 1;

	underlying_type : 10;

	underlying_type nw : 1;
	underlying_type cd : 1;
	underlying_type pg : 1;

	[[nodiscard]] constexpr bool protected_enable() const noexcept { return pe; }
	[[nodiscard]] constexpr bool monitor_coprocessor() const noexcept { return mp; }
	[[nodiscard]] constexpr bool emulation() const noexcept { return em; }
	[[nodiscard]] constexpr bool task_switched() const noexcept { return ts; }
	[[nodiscard]] constexpr bool extension_type() const noexcept { return et; }
	[[nodiscard]] constexpr bool numeric_error() const noexcept { return ne; }
	[[nodiscard]] constexpr bool write_protect() const noexcept { return wp; }
	[[nodiscard]] constexpr bool alignment_mask() const noexcept { return am; }
	[[nodiscard]] constexpr bool not_write_through() const noexcept { return nw; }
	[[nodiscard]] constexpr bool cache_disable() const noexcept { return cd; }
	[[nodiscard]] constexpr bool paging() const noexcept { return pg; }
};

using control1 = ::std::uint32_t;

using control2 = ::std::uint32_t;

struct control3
{
	NGS_MPL_ENVIRON_BEGIN(control3);
public:
	using underlying_type = ::std::uint32_t;

	constexpr static self_type create(underlying_type value)
	{
		if (::std::is_constant_evaluated())
		{
			return {
				.pwt = static_cast<::std::uint32_t>(value >> 3),
				.pcd = static_cast<::std::uint32_t>(value >> 4),
				.base = static_cast<::std::uint32_t>(value >> 12),
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
			return (pwt << 3) | (pcd << 4) | (base << 12);
		}
		else
		{
			return *reinterpret_cast<const underlying_type*>(this);
		}
	}
	

	underlying_type : 3;
	underlying_type pwt : 1;
	underlying_type pcd : 1;
	underlying_type : 7;
	underlying_type base : 20;
};

struct control4
{
	NGS_MPL_ENVIRON_BEGIN(control4);
public:
	using underlying_type = ::std::uint32_t;

	constexpr static self_type create(underlying_type value)
	{
		if (::std::is_constant_evaluated())
		{
			return {
				.vme = static_cast<::std::uint32_t>(value >> 0),
				.pvi = static_cast<::std::uint32_t>(value >> 1),
				.tsd = static_cast<::std::uint32_t>(value >> 2),
				.de = static_cast<::std::uint32_t>(value >> 3),
				.pse = static_cast<::std::uint32_t>(value >> 4),
				.pae = static_cast<::std::uint32_t>(value >> 5),
				.mce = static_cast<::std::uint32_t>(value >> 6),
				.pge = static_cast<::std::uint32_t>(value >> 7),
				.pce = static_cast<::std::uint32_t>(value >> 8),
				.osfxsr = static_cast<::std::uint32_t>(value >> 9),
				.osxmmexcpt = static_cast<::std::uint32_t>(value >> 10),
				.vmxe = static_cast<::std::uint32_t>(value >> 13),
				.smxe = static_cast<::std::uint32_t>(value >> 14),
				.pcide = static_cast<::std::uint32_t>(value >> 17),
				.osxsave = static_cast<::std::uint32_t>(value >> 18),
				.smep = static_cast<::std::uint32_t>(value >> 20),
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
			return (vme << 0) | (pvi << 1) | (tsd << 2) | (de << 3) | (pse << 4) | (pae << 5) | (mce << 6) | (pge << 7) | (pce << 8) | (osfxsr << 9) | (osxmmexcpt << 10) | (vmxe << 13) | (smxe << 14) | (pcide << 17) | (osxsave << 18) | (smep << 20);
		}
		else
		{
			return *reinterpret_cast<const underlying_type*>(this);
		}
	}

	underlying_type vme : 1;
	underlying_type pvi : 1;
	underlying_type tsd : 1;
	underlying_type de : 1;
	underlying_type pse : 1;
	underlying_type pae : 1;
	underlying_type mce : 1;
	underlying_type pge : 1;

	underlying_type pce : 1;
	underlying_type osfxsr : 1;
	underlying_type osxmmexcpt : 1;
	underlying_type : 2;
	underlying_type vmxe : 1;
	underlying_type smxe : 1;
	underlying_type : 2;
	underlying_type pcide : 1;
	underlying_type osxsave : 1;
	underlying_type : 1;
	underlying_type smep : 1;
};

NGS_LIB_MODULE_END
