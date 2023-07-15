#pragma once

#include "NGS/ngl/defined.h"
#include "NGS/ngl/context.h"
#include "NGS/ngl/gl_enum.h"
#include "NGS/ngl/gl/error.h"

NGLGL_BEGIN


_NGL_DECALRE_CONTEXT(Renderbuffer, GLuint) {
private:
	static void _GENERATE(handle_type & handle) { glGenRenderbuffers(1, &handle); }
	static void _DESTROY(handle_type & handle) { glDeleteRenderbuffers(1, &handle); }
public:
	_NGL_CONTEXT_DEFAULT_CONSTRUCTOR(Renderbuffer);
};

_NGL_DECALRE_CURRENT(Renderbuffer) {
	constexpr static auto type = GL_RENDERBUFFER;
	_NGL_CURRENT_DEFAULT_CONSTRUCTOR(Renderbuffer) { _NGL_CHECK(glBindRenderbuffer(type, context)); }
public:

	void SetStorage(RenderbufferImageFormat internal_format, size_t width, size_t height) {
		_NGL_CHECK(glRenderbufferStorage(type, (GLenum)internal_format, width, height));
	}
};

NGLGL_END
