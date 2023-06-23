#pragma once

#include "NGL/defined.h"
#include "NGL/opengl.h"

NGLGL_BEGIN

enum class ErrorCode {
	no_error = GL_NO_ERROR,
	invalid_enum = GL_INVALID_ENUM,
	invalid_value = GL_INVALID_VALUE,
	invalid_operation = GL_INVALID_OPERATION,
	invalid_framebuffer_operation = GL_INVALID_FRAMEBUFFER_OPERATION,
	out_of_memory = GL_OUT_OF_MEMORY,
	stack_underflow = GL_STACK_UNDERFLOW,
	stack_overflow = GL_STACK_OVERFLOW,
};

class Error {
public:
	static void CLEAR() { while (glGetError()); }

	static ErrorCode GET() { return (ErrorCode)glGetError(); }
};

#define _NGL_CHECK(func)\
Error::CLEAR();			\
func;					\
do{						\
	auto code = Error::GET();\
	NGS_ASSERT(Error::GET() == ErrorCode::no_error, Format("OpenGL Error code %d", code).c_str());\
} while (false)			\
//

NGLGL_END
