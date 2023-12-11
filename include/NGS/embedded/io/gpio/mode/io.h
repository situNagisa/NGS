#pragma once

#include "./defined.h"

NGS_LIB_MODULE_BEGIN
namespace modes
{
	enum class NGS_DLL_API io {
		disable,
		input,
		output,
		output_open_drain,
		input_output_open_drain,
		input_output,
	};
}
NGS_LIB_MODULE_END