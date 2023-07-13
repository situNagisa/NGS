#pragma once

#include "NGS/ngl/defined.h"
#include "NGS/ngl/context.h"
#include "NGS/ngl/gl/error.h"
#include "NGS/ngl/gl_enum.h"

NGLGL_BEGIN

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

	void Viewport(int x, int y, size_t width, size_t height) {
		_NGL_CHECK(glViewport(x, y, width, height));
	}
};
_NGL_CURRENT_INSTANCE(state, State);

NGLGL_END
