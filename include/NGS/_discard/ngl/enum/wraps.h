#pragma once

#include "NGS/ngl/defined.h"

NGL_BEGIN

enum class  Wraps : GLint {
	repeat = GL_REPEAT,
	mirrored_repeat = GL_MIRRORED_REPEAT,
	clamp_to_edge = GL_CLAMP_TO_EDGE,
	clamp_to_border = GL_CLAMP_TO_BORDER,
};

NGL_END
