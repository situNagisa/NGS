#pragma once

#include "NGS/external/opengl_new/enum.h"
#include "NGS/assert/assert.h"

#include "../defined.h"

#ifndef NGS_EXTERNAL_OPENGL_ERROR_CONFIG_DEBUG_GL_FUNCTION
#	define NGS_EXTERNAL_OPENGL_ERROR_SHOW_GL_FUNCTION(func) 
#else
#	define NGS_EXTERNAL_OPENGL_ERROR_SHOW_GL_FUNCTION(func) NGS_LOGL(debug,#func)
#endif

#define NGS_EXTERNAL_OPENGL_ERROR_NS NGS_EXTERNAL_OPENGL_NS::error

#define NGS_LIB_VERSION_MAJOR 0
#define NGS_LIB_VERSION_MINOR 1
#define NGS_LIB_VERSION_PATCH 0
#define NGS_LIB_NAME NGS_EXTERNAL_OPENGL_ERROR_NS
#include "NGS/lib/lib.h"

NGS_LIB_BEGIN

class NGS_DLL_API error {
public:
	static void clear() { while (::glGetError()); }

	static enums::error_code get() { return static_cast<enums::error_code>(::glGetError()); }
};

#define NGS_EXTERNAL_OPENGL_ERROR_CHECK(func)																			\
do{																														\
	NGS_NS::NGS_EXTERNAL_OPENGL_ERROR_NS::error::clear();																\
	func;																												\
	NGS_EXTERNAL_OPENGL_ERROR_SHOW_GL_FUNCTION(func);																	\
	do {																												\
		auto code = NGS_NS::NGS_EXTERNAL_OPENGL_ERROR_NS::error::get();													\
		NGS_ASSERT(code == NGS_NS::NGS_EXTERNAL_OPENGL_NS::enums::error_code::no_error, NGS_NS::fmt::c("opengl error code %d", code).c_str());\
	} while (false);																									\
}while(false)																											\
//

NGS_LIB_END

#include "NGS/lib/lib_end.h"