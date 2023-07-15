#pragma once

#include "NGS/ngl/defined.h"
#include "NGS/ngl/opengl.h"
#include "NGS/ngl/gl_enum.h"	
#include "NGS/ngl/config.h"

NGLGL_BEGIN

class Error {
public:
	static void CLEAR() { while (glGetError()); }

	static ErrorCode GET() { return (ErrorCode)glGetError(); }
};

#define _NGL_CHECK(func)\
ngl::gl::Error::CLEAR();\
func;					\
NGL_SHOW_GL_FUNC(func);	\
do{						\
	auto code = ngl::gl::Error::GET();\
	NGS_ASSERT(ngl::gl::Error::GET() == ngl::ErrorCode::no_error, ngs::Format("OpenGL Error code %d", code).c_str());\
} while (false)			\
//

NGLGL_END
