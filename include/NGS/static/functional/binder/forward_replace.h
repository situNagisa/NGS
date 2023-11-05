#pragma once

#include "./concept.h"
#include "../packer.h"

NGS_STATIC_FUNCTIONAL_BEGIN

constexpr decltype(auto) forward_replace(is_binder auto&& binder, auto&&... params)
{
	return binder(NGS_PP_PERFECT_FORWARD(params)...);
}

NGS_STATIC_FUNCTIONAL_END