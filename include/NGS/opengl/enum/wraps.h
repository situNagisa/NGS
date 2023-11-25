#pragma once

#include "./defined.h"

NGS_OPENGL_ENUM_BEGIN

enum class NGS_DLL_API wraps : gl_enum_t {
	repeat = GL_REPEAT,
	mirrored_repeat = GL_MIRRORED_REPEAT,
	clamp_to_edge = GL_CLAMP_TO_EDGE,
	clamp_to_border = GL_CLAMP_TO_BORDER,
};

NGS_OPENGL_ENUM_END
