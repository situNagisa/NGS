#pragma once

#include "./defined.h"

NGS_LIB_MODULE_BEGIN


enum class NGS_DLL_API filters : gl_enum_t {
	nearest = GL_NEAREST,
	linear = GL_LINEAR,
	nearest_mipmap_nearest = GL_NEAREST_MIPMAP_NEAREST,
	linear_mipmap_nearest = GL_LINEAR_MIPMAP_NEAREST,
	nearest_mipmap_linear = GL_NEAREST_MIPMAP_LINEAR,
	linear_mipmap_linear = GL_LINEAR_MIPMAP_LINEAR,
};

NGS_LIB_MODULE_END
