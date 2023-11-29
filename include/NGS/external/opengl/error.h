#pragma once

#include "./defined.h"
#include "./opengl.h"
#include "./enum.h"	
#include "./config.h"

NGS_OPENGL_BEGIN

class NGS_DLL_API error {
public:
	static void clear() { while (glGetError()); }

	static enums::error_code get() { return static_cast<enums::error_code>(glGetError()); }
};

#define NGS_OPENGL_CHECK(func)																							\
do{																														\
	NGS_ opengl::error::clear();																						\
	func;																												\
	NGS_OPENGL_SHOW_GL_FUNC(func);																						\
	do {																												\
		auto code = NGS_ opengl::error::get();																			\
		NGS_ASSERT(code == NGS_ opengl::enums::error_code::no_error, NGS_ format("OpenGL Error code %d", code).c_str());\
	} while (false);																									\
}while(false)																											\
//

NGS_OPENGL_END
