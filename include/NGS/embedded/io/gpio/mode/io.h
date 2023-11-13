#pragma once

#include "./defined.h"

NGS_EMBEDDED_IO_GPIO_MODE_BEGIN

enum class NGS_DLL_API io {
	disable,
	input,
	output,
	output_open_drain,
	input_output_open_drain,
	input_output,
};

NGS_EMBEDDED_IO_GPIO_MODE_END