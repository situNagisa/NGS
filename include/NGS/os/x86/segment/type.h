#pragma once

#include "./defined.h"

NGS_LIB_MODULE_BEGIN

struct segment_info
{
	NGS_MPL_ENVIRON_BEGIN(segment_info);
public:
	using underlying_type = ::std::uint8_t;

	enum class segment_type : underlying_type
	{
		data = 0,
		code = 1,
	};

	constexpr static self_type create(underlying_type value)
	{
		if (::std::is_constant_evaluated())
		{
			return self_type{
				.accessible = static_cast<underlying_type>(value & 0x01),
				.writable_or_conforming = static_cast<underlying_type>(value & 0x02),
				.expand_down_or_readable = static_cast<underlying_type>(value & 0x04),
				.type = static_cast<segment_type>(value & 0x08),
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
			return accessible | (writable_or_conforming << 1) | (expand_down_or_readable << 2) | (static_cast<underlying_type>(type) << 3);
		}
		else
		{
			return *reinterpret_cast<const underlying_type*>(this);
		}
	}

	underlying_type accessible : 1;
	underlying_type writable_or_conforming : 1;
	underlying_type expand_down_or_readable : 1;
	segment_type type : 1;
};


NGS_LIB_MODULE_END