#pragma once

#include "NGL/defined.h"
#include "NGL/opengl.h"
#include "NGL/gl/context.h"

NGL_BEGIN

class EBO_Context {
public:

	operator bool()const { return _handle; }
private:
	GLuint _handle = 0;
};
static_assert(Context<EBO_Context>, "concept error");

class EBO : public GL_ContextManager<EBO_Context> {
public:

	static __context_ref GetContext();
	static void SetContext(__context_ref_cst context);
private:

private:
	__context_ptr _current = nullptr;
};
static_assert(ContextManager<EBO, EBO_Context>, "concept error");

NGL_END

