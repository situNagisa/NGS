#pragma once

#include "./enum_under.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

struct segment_descriptor
{
	NGS_MPL_ENVIRON_BEGIN(segment_descriptor);
public:
	using underlying_type = ::std::uint64_t;

	underlying_type limit_low : 16;
	underlying_type base_low : 16;
	underlying_type base_middle : 8;
	underlying_type type : 4;
	underlying_type s : 1;
	underlying_type dpl : 2;
	underlying_type p : 1;
	underlying_type limit_high : 4;
	underlying_type avl : 1;
	underlying_type l : 1;
	underlying_type db : 1;
	underlying_type g : 1;
	underlying_type base_high : 8;

	constexpr static auto create(
		underlying_type base,
		underlying_type limit,
		underlying_type segment,
		underlying_type descriptor_type,
		enum_under<underlying_type> auto privilege_level,
		bool present = false,
		underlying_type available = {},
		underlying_type mode = {},
		underlying_type operation_size = {},
		underlying_type granularity = {}
	)
	{
		return self_type{
			.limit_low = static_cast<underlying_type>(bits::algorithm::span_value(limit,0,16)),
			.base_low = static_cast<underlying_type>(bits::algorithm::span_value(base,0,16)),
			.base_middle = static_cast<underlying_type>(bits::algorithm::span_value(base,16,8)),
			.type = static_cast<underlying_type>(segment),
			.s = (descriptor_type),
			.dpl = static_cast<underlying_type>(privilege_level),
			.p = static_cast<underlying_type>(present),
			.limit_high = static_cast<underlying_type>(bits::algorithm::span_value(limit,16,4)),
			.avl = static_cast<underlying_type>(available),
			.l = (mode),
			.db = (operation_size),
			.g = (granularity),
			.base_high = static_cast<underlying_type>(bits::algorithm::span_value(base,24,8)),
		};
	}
};

NGS_LIB_MODULE_END