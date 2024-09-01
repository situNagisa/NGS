#pragma once

#include "./core.h"

NGS_LIB_BEGIN

constexpr decltype(auto) make(auto&&... args)
{
	return tuple<decltype(args)...>(NGS_PP_PERFECT_FORWARD(args)...);
}

NGS_LIB_END