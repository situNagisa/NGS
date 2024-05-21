#pragma once

#include "./control.h"
#include "./defined.h"

NGS_LIB_BEGIN

template<controls::control_0 Control>
struct cpu
{
	constexpr static auto control0 = Control;

	constexpr auto segment_addressing(::std::uint32_t visual_address) const
	{
		
	}
};

NGS_LIB_END