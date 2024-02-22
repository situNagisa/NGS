#pragma once

#include "./enum.h"	
#include "./config.h"
#include "./defined.h"

NGS_LIB_BEGIN

class NGS_DLL_API error {
public:
	static void clear() { while (glGetError()); }

	static enums::error_code get() { return static_cast<enums::error_code>(glGetError()); }
};

#define NGS_EXTERNAL_OPENGL_CHECK(func)																					\
do{																														\
	NGS_LIB_FULL_QUALIFIER_NAME::error::clear();																		\
	func;																												\
	NGS_OPENGL_SHOW_GL_FUNC(func);																						\
	do {																												\
		auto code = NGS_LIB_FULL_QUALIFIER_NAME::error::get();																			\
		NGS_ASSERT(code == NGS_LIB_FULL_QUALIFIER_NAME::enums::error_code::no_error, fmt::c("OpenGL Error code %d", code).c_str());\
	} while (false);																									\
}while(false)																											\
//

NGS_LIB_END
