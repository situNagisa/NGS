#pragma once

#include "./defined.h"

NGS_OPENGL_ENUM_BEGIN


enum class NGS_DLL_API error_code : gl_enum_t {
	no_error = GL_NO_ERROR,
	invalid_enum = GL_INVALID_ENUM,
	invalid_value = GL_INVALID_VALUE,
	invalid_operation = GL_INVALID_OPERATION,
	invalid_framebuffer_operation = GL_INVALID_FRAMEBUFFER_OPERATION,
	out_of_memory = GL_OUT_OF_MEMORY,
	stack_underflow = GL_STACK_UNDERFLOW,
	stack_overflow = GL_STACK_OVERFLOW,
};

NGS_OPENGL_ENUM_END
