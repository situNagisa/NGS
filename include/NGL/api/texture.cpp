#include "NGL/api/texture.h"

NGL_BEGIN

Texture2D::Texture2D(void_ptr_cst data, size_t width, size_t height, GLenum format)
	: _context(gl::texture_2d.Create())
{
	auto& texture = ngl::gl::texture_2d;
	texture.SetContext(_context);
	texture.Generate(data, width, height, gl_convert<byte>, format, format);
	texture.SetWrap(ngl::gl::Wraps::repeat, ngl::gl::Wraps::repeat);
	texture.SetFilter(ngl::gl::Filters::linear_mipmap_linear, ngl::gl::Filters::linear);
	texture.GenerateMipmap();
	texture.SetContextNull();
}

NGL_END