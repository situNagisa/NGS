#pragma once

#include "./defined.h"

NGS_LIB_MODULE_BEGIN

struct local_descriptor_table
{
	NGS_MPL_ENVIRON_BEGIN(local_descriptor_table);
public:
	using underlying_type = ::std::uint16_t;
	enum class table_indicator : underlying_type
	{
		global = 0,
		local = 1
	};

	constexpr static self_type create(underlying_type value)
	{
		if (::std::is_constant_evaluated())
		{
			return {
				.rpl = static_cast<underlying_type>((value >> 0) & 0x03),
				.ti = static_cast<enum table_indicator>((value >> 2) & 0x01),
				.index = static_cast<underlying_type>((value >> 3) & 0x0FFF),
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
				(static_cast<underlying_type>(rpl) << 0)
				| (static_cast<underlying_type>(ti) << 2)
				| (static_cast<underlying_type>(index) << 3)
				;
		}
		else
		{
			return *reinterpret_cast<const underlying_type*>(this);
		}
	}

	

	underlying_type rpl : 2;
	table_indicator ti : 1;
	underlying_type index : 13;

	[[nodiscard]] constexpr auto privilege()const { return rpl; }
	[[nodiscard]] constexpr table_indicator table_indicator() const { return ti; }
};

NGS_LIB_MODULE_END
