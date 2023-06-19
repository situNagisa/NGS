#pragma once

#include "NGL/defined.h"
#include "NGL/gl/context.h"

NGL_BEGIN

template<class _Context>
class GL_ContextManager {
public:
	NGS_TYPE_DEFINE(_Context, context);
public:

	static_assert(ContextManager<GL_ContextManager<__context>, __context>, "GL_ContextManager must satisfy ContextManager concept");
};


NGL_END
