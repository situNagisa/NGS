#pragma once

#include "./defined.h"

NGS_LIB_MODULE_BEGIN

struct extended_flags
{
	NGS_MPL_ENVIRON_BEGIN(extended_flags);
public:
	using underlying_type = ::std::uint32_t;

	constexpr static self_type create(underlying_type value)
	{
		if (::std::is_constant_evaluated())
		{
			return {
				.cs = static_cast<underlying_type>(value >> 0),
				.pf = static_cast<underlying_type>(value >> 2),
				.af = static_cast<underlying_type>(value >> 4),
				.zf = static_cast<underlying_type>(value >> 6),
				.sf = static_cast<underlying_type>(value >> 7),
				.tf = static_cast<underlying_type>(value >> 8),
				.if_ = static_cast<underlying_type>(value >> 9),
				.df = static_cast<underlying_type>(value >> 10),
				.of = static_cast<underlying_type>(value >> 11),
				.iopl = static_cast<underlying_type>(value >> 12),
				.nt = static_cast<underlying_type>(value >> 14),
				.rf = static_cast<underlying_type>(value >> 16),
				.vm = static_cast<underlying_type>(value >> 17),
				.ac = static_cast<underlying_type>(value >> 18),
				.vif = static_cast<underlying_type>(value >> 19),
				.vip = static_cast<underlying_type>(value >> 20),
				.id = static_cast<underlying_type>(value >> 21),
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
			return
				(static_cast<underlying_type>(cs) << 0) |
				(static_cast<underlying_type>(pf) << 2) |
				(static_cast<underlying_type>(af) << 4) |
				(static_cast<underlying_type>(zf) << 6) |
				(static_cast<underlying_type>(sf) << 7) |
				(static_cast<underlying_type>(tf) << 8) |
				(static_cast<underlying_type>(if_) << 9) |
				(static_cast<underlying_type>(df) << 10) |
				(static_cast<underlying_type>(of) << 11) |
				(static_cast<underlying_type>(iopl) << 12) |
				(static_cast<underlying_type>(nt) << 14) |
				(static_cast<underlying_type>(rf) << 16) |
				(static_cast<underlying_type>(vm) << 17) |
				(static_cast<underlying_type>(ac) << 18) |
				(static_cast<underlying_type>(vif) << 19) |
				(static_cast<underlying_type>(vip) << 20) |
				(static_cast<underlying_type>(id) << 21);
		}
		else
		{
			return *reinterpret_cast<const underlying_type*>(this);
		}
	}

	underlying_type cs : 1;
	underlying_type	   : 1;
	underlying_type pf : 1;
	underlying_type    : 1;
	underlying_type af : 1;
	underlying_type    : 1;
	underlying_type zf : 1;
	underlying_type sf : 1;
	underlying_type tf : 1;
	underlying_type if_ : 1;
	underlying_type df : 1;
	underlying_type of : 1;
	underlying_type iopl : 2;
	underlying_type nt : 1;
	underlying_type    : 1;
	underlying_type rf : 1;
	underlying_type vm : 1;
	underlying_type ac : 1;
	underlying_type vif : 1;
	underlying_type vip : 1;
	underlying_type id : 1;
	underlying_type    : 10;
};

NGS_LIB_MODULE_END