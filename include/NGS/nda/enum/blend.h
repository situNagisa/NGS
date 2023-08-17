#pragma once

#include "NGS/nda/defined.h"

NDA_BEGIN

enum class  BlendMode {
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
	hardlight,
	shader,
};

NDA_END
