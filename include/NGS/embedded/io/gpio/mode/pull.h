#pragma once

#include "./defined.h"

NGS_EMBEDDED_IO_GPIO_MODE_BEGIN

enum class NGS_DLL_API pull {
	up,
	down,
	up_down,
	floating,
};

NGS_EMBEDDED_IO_GPIO_MODE_END