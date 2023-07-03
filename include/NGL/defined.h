#pragma once

#include "NGS/base/base.h"
#include "NGS/extend/extend.h"
#include "NGS/math/math.h"

#include "NGL/opengl.h"

#define NGL_BEGIN NGS_BEGIN namespace ngl{
#define NGL_END } NGS_END

#define NGLGL_BEGIN NGL_BEGIN namespace gl{
#define NGLGL_END } NGL_END

NGL_BEGIN

NGS_DECLARE_TV(gl, GLuint);
NGS_DEFINE_TV(gl, GLuint, float32, GL_FLOAT);
NGS_DEFINE_TV(gl, GLuint, float64, GL_DOUBLE);
NGS_DEFINE_TV(gl, GLuint, int8, GL_BYTE);
NGS_DEFINE_TV(gl, GLuint, uint8, GL_UNSIGNED_BYTE);
NGS_DEFINE_TV(gl, GLuint, int16, GL_SHORT);
NGS_DEFINE_TV(gl, GLuint, uint16, GL_UNSIGNED_SHORT);
NGS_DEFINE_TV(gl, GLuint, int32, GL_INT);
NGS_DEFINE_TV(gl, GLuint, uint32, GL_UNSIGNED_INT);

NGS_DEFINE_TV(gl, GLuint, RGBA24, GL_RGB);
NGS_DEFINE_TV(gl, GLuint, RGBA32, GL_RGBA);

#undef NGL_TYPE_VALUE_MAP

NGL_END

namespace ngl = ::ngs::ngl;