#pragma once

#include "NGL/defined.h"
#include "NGL/context.h"
#include "NGL/gl/error.h"

NGLGL_BEGIN

class Renderer {
private:
	friend class Constructor;
	Renderer() = default;
public:
	void Clear(GLbitfield mask) { _NGL_CHECK(glClear(mask)); }
	void ClearColor(StdARGB argb) {
		_NGL_CHECK(glClearColor(
			StdARGB::R::Percent(argb.Red()),
			StdARGB::G::Percent(argb.Green()),
			StdARGB::B::Percent(argb.Blue()),
			StdARGB::A::Percent(argb.Alpha())
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
