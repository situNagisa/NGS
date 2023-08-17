#pragma once

#include "NGS/dl/defined.h"

NGS_DL_BEGIN

enum class NGS_API BlendMode {
	normal,
	layer,
	multiply,
	screen,
	lighten,
	darken,
	difference,
	add,
	substract,
	invert,
	alpha,
	erase,
	overlay,
	hard_light,
	shader,
};

NGS_DL_END
