#pragma once

#include "NGS/ngl/defined.h"
#include "NGS/ngl/opengl.h"
#include "NGS/ngl/gl/gl.h"

NGL_BEGIN

class Texture2D {
public:
	Texture2D(void_ptr_cst data, size_t width, size_t height, GLenum format)
		: _context(gl::texture_2d.Create())
	{
		auto& texture = ngl::gl::texture_2d;
		Active();
		texture.Generate(data, width, height, gl_convert<byte>, format, format);
		texture.SetWrap(gl::Wraps::repeat, gl::Wraps::repeat);
		texture.SetFilter(gl::Filters::linear_mipmap_linear, gl::Filters::linear);
		texture.GenerateMipmap();
		Deactivate();
	}
	template<CSameAsAny<RGBA24, RGBA32> _RGBA>
	Texture2D(const _RGBA* data, size_t width, size_t height)
		: Texture2D(data, width, height, gl_convert<_RGBA>)
	{}

	~Texture2D() = default;

	void Active() { gl::texture_2d.PushContext(_context); }
	void Deactivate() { gl::texture_2d.PopContext(); }

private:
	gl::Texture2DContext _context = {};
};


NGL_END
