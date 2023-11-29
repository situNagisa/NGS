#pragma once

#include "NGS/basic/basic.h"
#include "NGS/color/color.h"
#include "NGS/log/log.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define NGS_OPENGL_BEGIN NGS_BEGIN namespace opengl{
#define NGS_OPENGL_END } NGS_END

NGS_OPENGL_BEGIN

using fundamental_t = GLuint;
using context_t = GLuint;
using pixel_internal_format_t = GLint;
using pixel_format_t = GLenum;
using gl_enum_t = GLenum;

NGS_DECLARE_TV(gl, fundamental_t);
NGS_DEFINE_TV(gl, fundamental_t, float32, GL_FLOAT);
NGS_DEFINE_TV(gl, fundamental_t, float64, GL_DOUBLE);
NGS_DEFINE_TV(gl, fundamental_t, int8, GL_BYTE);
NGS_DEFINE_TV(gl, fundamental_t, uint8, GL_UNSIGNED_BYTE);
NGS_DEFINE_TV(gl, fundamental_t, int16, GL_SHORT);
NGS_DEFINE_TV(gl, fundamental_t, uint16, GL_UNSIGNED_SHORT);
NGS_DEFINE_TV(gl, fundamental_t, int32, GL_INT);
NGS_DEFINE_TV(gl, fundamental_t, uint32, GL_UNSIGNED_INT);

NGS_DEFINE_TV(gl, fundamental_t, colors::RGBA24, GL_RGB);
NGS_DEFINE_TV(gl, fundamental_t, colors::RGBA32, GL_RGBA);

NGS_OPENGL_END