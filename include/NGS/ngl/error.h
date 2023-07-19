#pragma once

#include "NGS/ngl/defined.h"
#include "NGS/ngl/opengl.h"
#include "NGS/ngl/gl_enum.h"	
#include "NGS/ngl/config.h"

NGL_BEGIN

class Error {
public:
	static void CLEAR() { while (glGetError()); }

	static ErrorCode GET() { return (ErrorCode)glGetError(); }
};

#define NGL_CHECK(func)\
ngl::Error::CLEAR();	\
func;					\
NGL_SHOW_GL_FUNC(func);	\
do{						\
	auto code = ngl::Error::GET();\
	NGS_ASSERT(ngl::Error::GET() == ngl::ErrorCode::no_error, ngs::Format("OpenGL Error code %d", code).c_str());\
} while (false)			\
//

NGL_END
