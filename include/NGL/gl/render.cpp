#include "NGL/gl/render.h"

NGLGL_BEGIN

void Renderer::Clear(GLbitfield mask)
{
	glClear(mask);
}

void Renderer::ClearColor(StdARGB argb)
{
	glClearColor(
		StdARGB::R::Percent(argb.Red()),
		StdARGB::G::Percent(argb.Green()),
		StdARGB::B::Percent(argb.Blue()),
		StdARGB::A::Percent(argb.Alpha())
	);
}

void Renderer::ClearDepth(GLdouble depth)
{
	glClearDepth(depth);
}

void Renderer::ClearStencil(GLint s)
{
	glClearStencil(s);
}

void Renderer::DrawBuffer(GLenum buffer)
{
	glDrawBuffer(buffer);
}

NGLGL_END
