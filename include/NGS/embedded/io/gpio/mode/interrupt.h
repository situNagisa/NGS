#pragma once

#include "./defined.h"

NGS_LIB_MODULE_BEGIN
namespace modes
{
	enum class NGS_DLL_API interrupt {
		disable,
		positive,
		negative,
		any,
		low,
		high,
		max,
	};
}
NGS_LIB_MODULE_END