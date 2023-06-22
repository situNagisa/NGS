#pragma once

#include "NGL/defined.h"
#include "NGL/context.h"

NGLGL_BEGIN

class Renderer {
private:
	friend class Constructor;
	Renderer() = default;
public:
	void Clear(GLbitfield mask);
	void ClearColor(StdARGB argb);
	void ClearDepth(GLdouble depth);
	void ClearStencil(GLint s);
	void DrawBuffer(GLenum buffer);
	void Finish();
	void Flush();
	void ReadBuffer();
	void ReadPixels();
};
_NGL_CURRENT_INSTANCE(renderer, Renderer);

NGLGL_END
