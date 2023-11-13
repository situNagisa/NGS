#pragma once

#include "./defined.h"

NGS_EMBEDDED_IO_GPIO_MODE_BEGIN

enum class NGS_DLL_API interrupt {
	disable,
	positive,
	negative,
	any,
	low,
	high,
	max,
};

NGS_EMBEDDED_IO_GPIO_MODE_END