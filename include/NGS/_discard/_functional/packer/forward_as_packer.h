#pragma once

#include "./packer.h"
#include "../param.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

constexpr decltype(auto) forward_as_packer(is_param auto&&... params)
{
	return packer(NGS_PP_PERFECT_FORWARD(params)...);
}

NGS_LIB_MODULE_END
NGS_LIB_MODULE_EXPORT(forward_as_packer);