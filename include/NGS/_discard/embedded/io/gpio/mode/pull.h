#pragma once

#include "./defined.h"


NGS_LIB_MODULE_BEGIN
namespace modes
{
	enum class NGS_DLL_API pull {
		up,
		down,
		up_down,
		floating,
	};
}
NGS_LIB_MODULE_END