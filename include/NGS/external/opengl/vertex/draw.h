#pragma once

#include "../enum.h"
#include "./array.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

void draw(const basic_vertex_array& array, enums::draw_mode draw_mode, size_t offset, size_t count)
{

	NGS_EXTERNAL_OPENGL_CHECK(::glDrawArrays(static_cast<GLenum>(draw_mode), static_cast<GLint>(offset), static_cast<GLsizei>(count)));
}

NGS_LIB_MODULE_END