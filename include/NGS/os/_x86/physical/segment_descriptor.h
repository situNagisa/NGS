#pragma once

#include "./enum_under.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

struct segment_descriptor
{
	NGS_PP_INJECT_BEGIN(segment_descriptor);
public:
	using underlying_type = ::std::uint64_t;

	underlying_type limit_low : 16;
	underlying_type base_low : 16;
	underlying_type base_middle : 8;
	underlying_type type : 4;
	underlying_type s : 1;
	underlying_type descriptor_privilege : 2;
	underlying_type present : 1;
	underlying_type limit_high : 4;
	underlying_type avl : 1;
	underlying_type mode : 1;
	underlying_type db : 1;
	underlying_type granularity : 1;
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
			.limit_low = static_cast<underlying_type>(bits::algorithm::extract(limit,0,16)),
			.base_low = static_cast<underlying_type>(bits::algorithm::extract(base,0,16)),
			.base_middle = static_cast<underlying_type>(bits::algorithm::extract(base,16,8)),
			.type = static_cast<underlying_type>(segment),
			.s = (descriptor_type),
			.descriptor_privilege = static_cast<underlying_type>(privilege_level),
			.present = static_cast<underlying_type>(present),
			.limit_high = static_cast<underlying_type>(bits::algorithm::extract(limit,16,4)),
			.avl = static_cast<underlying_type>(available),
			.mode = (mode),
			.db = (operation_size),
			.granularity = (granularity),
			.base_high = static_cast<underlying_type>(bits::algorithm::extract(base,24,8)),
		};
	}
};

NGS_LIB_MODULE_END