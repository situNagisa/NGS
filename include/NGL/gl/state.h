#pragma once

#include "NGL/defined.h"
#include "NGL/context.h"

NGLGL_BEGIN

enum class Capabilities {
	blend = GL_BLEND,
	cull_face = GL_CULL_FACE,
	depth_test = GL_DEPTH_TEST,
	stencil_test = GL_STENCIL_TEST,
	scissor_test = GL_SCISSOR_TEST,
};

class State {
private:
	friend class Constructor;
	State() = default;
public:
	void Enable(Capabilities cap) { _NGL_CHECK(glEnable((GLenum)cap)); }
	template<class T>
	void Enable() { Enable(T::capability); }

	void Disable(Capabilities cap) { _NGL_CHECK(glDisable((GLenum)cap)); }
	template<class T>
	void Disable() { Disable(T::capability); }

	void Viewport(int32 x, int32 y, GLsizei width, GLsizei height) {
		_NGL_CHECK(glViewport(x, y, width, height));
	}
};
_NGL_CURRENT_INSTANCE(state, State);

NGLGL_END
