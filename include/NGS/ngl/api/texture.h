#pragma once

#include "NGS/ngl/defined.h"
#include "NGS/ngl/opengl.h"
#include "NGS/ngl/gl/gl.h"

NGL_BEGIN

class Texture2D {
public:
	Texture2D() = default;
	Texture2D(void_ptr_cst data, size_t width, size_t height, GLenum format)
		: _context(gl::instance::texture_2d.Create())
	{
		Initialize(data, width, height, format);
	}
	template<CSameAsAny<RGBA24, RGBA32> _RGBA>
	Texture2D(const _RGBA* data, size_t width, size_t height)
		: Texture2D(data, width, height, gl_convert<_RGBA>)
	{}

	Texture2D(Texture2D&& other)
		: _context(std::move(other._context))
	{}

	~Texture2D() = default;

	void Initialize(void_ptr_cst data, size_t width, size_t height, GLenum format) {
		auto& texture = ngl::gl::instance::texture_2d;
		Active();
		texture.Generate(data, width, height, gl_convert<byte>, format, format);
		texture.SetWrap(Wraps::repeat, Wraps::repeat);
		texture.SetFilter(Filters::linear_mipmap_linear, Filters::linear);
		texture.GenerateMipmap();
		Deactivate();
	}
	template<CSameAsAny<RGBA24, RGBA32> _RGBA>
	void Initialize(const _RGBA* data, size_t width, size_t height)
	{
		Initialize(data, width, height, gl_convert<_RGBA>);
	}

	void Active() { gl::instance::texture_2d.PushContext(_context); }
	void Deactivate() { gl::instance::texture_2d.PopContext(); }

private:
	gl::Texture2DContext _context = {};
};


NGL_END
