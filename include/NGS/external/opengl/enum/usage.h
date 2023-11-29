#pragma once

#include "./defined.h"

NGS_OPENGL_ENUM_BEGIN

enum class NGS_DLL_API usage : gl_enum_t {
	stream_draw = GL_STREAM_DRAW,
	stream_read = GL_STREAM_READ,
	stream_copy = GL_STREAM_COPY,

	static_draw = GL_STATIC_DRAW,
	static_read = GL_STATIC_READ,
	static_copy = GL_STATIC_COPY,

	dynamic_draw = GL_DYNAMIC_DRAW,
	dynamic_read = GL_DYNAMIC_READ,
	dynamic_copy = GL_DYNAMIC_COPY,
};

NGS_OPENGL_ENUM_END
