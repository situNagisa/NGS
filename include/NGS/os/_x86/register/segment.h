#pragma once

#include "./defined.h"

NGS_LIB_MODULE_BEGIN

struct data_segment
{
	NGS_MPL_ENVIRON_BEGIN(data_segment);
public:
	using underlying_type = ::std::uint16_t;

	constexpr static self_type create(underlying_type value)
	{
		return { .real = value };
	}

	constexpr explicit(false) operator underlying_type()const { return real; }

	enum class table_indicator : underlying_type
	{
		global = 0,
		local = 1
	};

	union
	{
		underlying_type real;
		struct _on_protected_mode
		{
			underlying_type rpl : 2;
			table_indicator ti : 1;
			underlying_type index : 13;
		}protect;
	};

	[[nodiscard]] constexpr auto privilege()const { return protect.rpl; }
	[[nodiscard]] constexpr table_indicator table_indicator() const { return protect.ti; }
};

using code_segment = ::std::uint16_t;
using stack_segment = ::std::uint16_t;


NGS_LIB_MODULE_END