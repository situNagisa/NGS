#pragma once

#include "./defined.h"

NGS_LIB_MODULE_BEGIN

struct local_descriptor_table
{
	NGS_PP_INJECT_BEGIN(local_descriptor_table);
public:
	using underlying_type = ::std::uint16_t;

	underlying_type rpl : 2;
	underlying_type ti : 1;
	underlying_type index : 13;
};

NGS_LIB_MODULE_END
