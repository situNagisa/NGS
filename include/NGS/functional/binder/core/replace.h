#pragma once

#include "./binder.h"

NGS_LIB_MODULE_BEGIN

constexpr decltype(auto) replace(is_binder auto&& binder, auto&&... args)
{
	return NGS_PP_PERFECT_FORWARD(binder)(NGS_PP_PERFECT_FORWARD(args)...);
}

NGS_LIB_MODULE_END
