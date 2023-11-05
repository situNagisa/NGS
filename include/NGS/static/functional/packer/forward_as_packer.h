#pragma once

#include "./packer.h"
#include "../param.h"

NGS_STATIC_FUNCTIONAL_BEGIN

constexpr decltype(auto) forward_as_packer(is_param auto&&... params)
{
	return packer(NGS_PP_PERFECT_FORWARD(params)...);
}

NGS_STATIC_FUNCTIONAL_END