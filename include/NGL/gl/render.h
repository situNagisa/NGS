#pragma once

#include "NGL/defined.h"
#include "NGL/context.h"
#include "NGL/gl/error.h"

NGLGL_BEGIN

//enum class BitField : GLbitfield {
//	color = GL_COLOR_BUFFER_BIT,
//	depth = GL_DEPTH_BUFFER_BIT,
//	stencil = GL_STENCIL_BUFFER_BIT,
//};

class Renderer {
private:
	friend class Constructor;
	Renderer() = default;
public:
	void Clear(GLbitfield mask) { _NGL_CHECK(glClear(mask)); }

	void ClearColor(StdRGBA argb) {
		_NGL_CHECK(glClearColor(
			(GLfloat)StdRGBA::R::Percent(argb.Red()),
			(GLfloat)StdRGBA::G::Percent(argb.Green()),
			(GLfloat)StdRGBA::B::Percent(argb.Blue()),
			(GLfloat)StdRGBA::A::Percent(argb.Alpha())
		));
	}
	void ClearDepth(GLdouble depth) { _NGL_CHECK(glClearDepth(depth)); }
	void ClearStencil(GLint s) { _NGL_CHECK(glClearStencil(s)); }
	void DrawBuffer(GLenum buffer) { _NGL_CHECK(glDrawBuffer(buffer)); }
	void Finish();
	void Flush();
	void ReadBuffer();
	void ReadPixels();
};
_NGL_CURRENT_INSTANCE(renderer, Renderer);

NGLGL_END
