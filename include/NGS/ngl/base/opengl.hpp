#pragma once

#include "NGS/ngl/base/opengl.h"
#include "NGS/ngl/vertex/array/base.h"
#include "NGS/ngl/base/buffer_target.h"
#include "NGS/ngl/texture/texture.hpp"
#include "NGS/ngl/shader/shader.h"

NGL_BEGIN

NGS_HPP_INLINE OpenGL::OpenGL()
	: buffer_target(new targets::BufferTarget())
	, vertex_array(new targets::VertexArray())
	, texture(new targets::Texture())
	, shader(new targets::ShaderProgram())
{
	NGS_LOGL(debug, "OpenGL init:");
	GLint max_uniforms;
	glGetIntegerv(GL_MAX_VERTEX_UNIFORM_COMPONENTS, &max_uniforms);
	NGS_PRINTFL("\tmax uniforms: %d", max_uniforms);

	GLint max_texture_units;
	glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &max_texture_units);
	NGS_PRINTFL("\tmax texture units: %d", max_texture_units);

	GLint max_texture_size;
	glGetIntegerv(GL_MAX_TEXTURE_SIZE, &max_texture_size);
	NGS_PRINTFL("\tmax texture size: %d", max_texture_size);

	GLint max_texture_buffer_size;
	glGetIntegerv(GL_MAX_TEXTURE_BUFFER_SIZE, &max_texture_buffer_size);
	NGS_PRINTFL("\tmax texture buffer size: %d", max_texture_buffer_size);

	NGS_PRINTL();
}

NGS_HPP_INLINE OpenGL::~OpenGL()
{
	delete buffer_target;
	delete vertex_array;
	delete texture;
	delete shader;
}

NGL_END
