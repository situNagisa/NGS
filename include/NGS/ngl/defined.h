#pragma once

#include "NGS/base/base.h"
#include "NGS/extend/extend.h"
#include "NGS/math/math.h"

#include "NGS/ngl/opengl.h"

#define NGL_BEGIN NGS_BEGIN namespace ngl{
#define NGL_END } NGS_END

#define NGLGL_BEGIN NGL_BEGIN namespace gl{
#define NGLGL_END } NGL_END

NGL_BEGIN

using type_t = GLuint;

NGS_DECLARE_TV(gl, type_t);
NGS_DEFINE_TV(gl, type_t, float32, GL_FLOAT);
NGS_DEFINE_TV(gl, type_t, float64, GL_DOUBLE);
NGS_DEFINE_TV(gl, type_t, int8, GL_BYTE);
NGS_DEFINE_TV(gl, type_t, uint8, GL_UNSIGNED_BYTE);
NGS_DEFINE_TV(gl, type_t, int16, GL_SHORT);
NGS_DEFINE_TV(gl, type_t, uint16, GL_UNSIGNED_SHORT);
NGS_DEFINE_TV(gl, type_t, int32, GL_INT);
NGS_DEFINE_TV(gl, type_t, uint32, GL_UNSIGNED_INT);

NGS_DEFINE_TV(gl, type_t, RGBA24, GL_RGB);
NGS_DEFINE_TV(gl, type_t, RGBA32, GL_RGBA);

#undef NGL_TYPE_VALUE_MAP

NGL_END

namespace ngl = ::ngs::ngl;