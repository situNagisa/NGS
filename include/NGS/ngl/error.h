#pragma once

#include "NGS/ngl/defined.h"
#include "NGS/ngl/opengl.h"
#include "NGS/ngl/gl_enum.h"	
#include "NGS/ngl/config.h"

NGL_BEGIN

class NGS_API  Error {
public:
	static void CLEAR() { while (glGetError()); }

	static ErrorCode GET() { return static_cast<ErrorCode>(glGetError()); }
};

#define NGL_CHECK(func)\
ngs::ngl::Error::CLEAR();	\
func;					\
NGL_SHOW_GL_FUNC(func);	\
do{						\
	auto code = ngs::ngl::Error::GET();\
	NGS_ASSERT(ngs::ngl::Error::GET() == ngs::ngl::ErrorCode::no_error, ngs::format("OpenGL Error code %d", code).c_str());\
} while (false)			\
//

NGL_END
