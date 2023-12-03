#pragma once

#include "NGS/base/base.h"
#include "NGS/mpl/mpl.h"
#include "NGS/extend/extend.h"
#include "NGS/math/math.h"
#include "NGS/ngl/opengl.h"
#include "NGS/mpl/structure.h"


#define NGL_BEGIN NGS_BEGIN namespace ngl{
#define NGL_END } NGS_END

#define NGL_FAC_BEGIN namespace factories{
#define NGL_BUF_BEGIN namespace buffers{
#define NGL_OBJ_BEGIN namespace objects{
#define NGL_TARGET_BEGIN namespace targets{

NGL_BEGIN

using type_t = GLuint;
using context_t = GLuint;
using internal_format_t = GLint;
using format_t = GLenum;

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


NGL_END