#pragma once

#include "../context.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

void shader_source(const contexts::basic_glsl& glsl, ::std::span<const ::GLchar* const> code)
{
	NGS_EXTERNAL_OPENGL_CHECK(::glShaderSource(glsl.get_context(), static_cast<::GLsizei>(code.size()), code.data(), nullptr));
}

void shader_source(const contexts::basic_glsl& glsl, const ::GLchar* code) { NGS_LIB_MODULE_NAME::shader_source(glsl, { &code,1 }); }

void shader_compile(const contexts::basic_glsl& glsl)
{
	NGS_EXTERNAL_OPENGL_CHECK(::glCompileShader(glsl.get_context()));
#if defined(NGS_BUILD_TYPE_IS_DEBUG)
	::GLint compile_ok = GL_FALSE;
	NGS_EXTERNAL_OPENGL_CHECK(::glGetShaderiv(glsl.get_context(), GL_COMPILE_STATUS, &compile_ok));
	if (compile_ok == GL_FALSE) {
		::GLint log_length;
		NGS_EXTERNAL_OPENGL_CHECK(::glGetShaderiv(glsl.get_context(), GL_INFO_LOG_LENGTH, &log_length));
		::std::string log{};
		log.resize(log_length);
		NGS_EXTERNAL_OPENGL_CHECK(::glGetShaderInfoLog(glsl.get_context(), log_length, NULL, log.data()));
		NGS_ASSERT(false, fmt::c("compile shader code fail! %s", log.c_str()));
	}
#endif
}

void shader_attach(const contexts::shader& shader, const contexts::basic_glsl& glsl)
{
	NGS_EXTERNAL_OPENGL_CHECK(::glAttachShader(shader.get_context(), glsl.get_context()));
}

void shader_link(const contexts::shader& shader)
{
	NGS_EXTERNAL_OPENGL_CHECK(::glLinkProgram(shader.get_context()));
#if NGS_BUILD_TYPE_IS_DEBUG
	//NGS_EXTERNAL_OPENGL_CHECK(::glValidateProgram(_context));
	::GLint status = GL_FALSE;
	NGS_EXTERNAL_OPENGL_CHECK(::glGetProgramiv(shader.get_context(), GL_LINK_STATUS, &status));
	if (status == GL_FALSE) {
		::GLint length;
		NGS_EXTERNAL_OPENGL_CHECK(glGetProgramiv(shader.get_context(), GL_INFO_LOG_LENGTH, &length));
		NGS_ASSERT(length, "get length fail!");
		::std::string info(length, 0);
		NGS_EXTERNAL_OPENGL_CHECK(glGetProgramInfoLog(shader.get_context(), length, &length, info.data()));
		NGS_ASSERT(false, fmt::c("link shader fail!\n %s", info.c_str()));
	}
#endif
}

::std::ptrdiff_t shader_uniform_location(const contexts::shader& shader, ::std::string_view uniform_name)
{
	::std::ptrdiff_t result;
	NGS_EXTERNAL_OPENGL_CHECK(result = ::glGetUniformLocation(shader.get_context(), uniform_name.data()));
	return result;
}

NGS_LIB_MODULE_END