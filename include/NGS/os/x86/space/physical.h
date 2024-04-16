#pragma once

#include "./basic_address.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

struct physical_address : basic_address
{
	NGS_MPL_ENVIRON(physical_address);
public:
	constexpr physical_address() = default;
	constexpr explicit(false) physical_address(typename base_type::underlying_type value)
		: base_type(value)
	{}
};

NGS_LIB_MODULE_END