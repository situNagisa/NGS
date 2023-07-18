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
{}

NGS_HPP_INLINE OpenGL::~OpenGL()
{
	delete buffer_target;
	delete vertex_array;
	delete texture;
	delete shader;
}

NGL_END
