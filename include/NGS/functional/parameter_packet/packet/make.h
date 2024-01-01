#pragma once

#include "./packet.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

constexpr auto make_packet(auto&&... args)
{
	return packet<decltype(args)...>(NGS_PP_PERFECT_FORWARD(args)...);
}

NGS_LIB_MODULE_END
