#pragma once

#include "NGS/ngl/defined.h"

NGL_BEGIN


enum class  Filters : GLint {
	nearest = GL_NEAREST,
	linear = GL_LINEAR,
	nearest_mipmap_nearest = GL_NEAREST_MIPMAP_NEAREST,
	linear_mipmap_nearest = GL_LINEAR_MIPMAP_NEAREST,
	nearest_mipmap_linear = GL_NEAREST_MIPMAP_LINEAR,
	linear_mipmap_linear = GL_LINEAR_MIPMAP_LINEAR,
};

NGL_END
