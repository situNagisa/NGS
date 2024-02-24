#pragma once

#include "../enum.h"
#include "./array.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

void draw_array(const vertex_array& array, enums::draw_mode draw_mode, ::std::size_t count, ::std::size_t offset = 0)
{

	NGS_EXTERNAL_OPENGL_CHECK(::glDrawArrays(static_cast<GLenum>(draw_mode), static_cast<GLint>(offset), static_cast<GLsizei>(count)));
}

void draw_elements(const vertex_array& array, enums::draw_mode draw_mode, ::std::size_t count, fundamental_t type, ::std::size_t offset = 0)
{
	NGS_EXTERNAL_OPENGL_CHECK(::glDrawElements(static_cast<GLenum>(draw_mode), static_cast<GLsizei>(count), static_cast<GLenum>(type), reinterpret_cast<const void*>(offset)));
}

NGS_LIB_MODULE_END