#pragma once

#include "NGL/defined.h"
#include "NGL/opengl.h"
#include "NGL/gl/gl.h"

NGL_BEGIN

class Texture2D {
public:
	Texture2D(void_ptr_cst data, size_t width, size_t height, GLenum format);
	template<ARGB_C _ARGB>
	Texture2D(const _ARGB* data, size_t width, size_t height)
		: Texture2D(data, width, height, convert<_ARGB>)
	{}

	~Texture2D() = default;
public:


private:
	gl::Texture2DContext _context = {};
};

NGL_END
