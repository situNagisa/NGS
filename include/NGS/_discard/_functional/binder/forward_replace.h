#pragma once

#include "./concept.h"
#include "../packer.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

constexpr decltype(auto) forward_replace(is_binder auto&& binder, auto&&... params)
{
	return binder(NGS_PP_PERFECT_FORWARD(params)...);
}

NGS_LIB_MODULE_END