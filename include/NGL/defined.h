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

template<class>
constexpr uint32 convert = 0;

template<uint32>
struct _Convert;

template<uint32 value>
using convert_t = _Convert<value>::type;

#define NGL_TYPE_VALUE_MAP(type_,value)		\
template<>									\
constexpr uint32 convert<type_> = value;	\
template<>									\
struct _Convert<value> { using type = type_; }\
//

NGL_TYPE_VALUE_MAP(float32, GL_FLOAT);
NGL_TYPE_VALUE_MAP(float64, GL_DOUBLE);
NGL_TYPE_VALUE_MAP(int8, GL_BYTE);
NGL_TYPE_VALUE_MAP(uint8, GL_UNSIGNED_BYTE);
NGL_TYPE_VALUE_MAP(int16, GL_SHORT);
NGL_TYPE_VALUE_MAP(uint16, GL_UNSIGNED_SHORT);
NGL_TYPE_VALUE_MAP(int32, GL_INT);
NGL_TYPE_VALUE_MAP(uint32, GL_UNSIGNED_INT);

NGL_TYPE_VALUE_MAP(ARGB24, GL_RGB);
NGL_TYPE_VALUE_MAP(ARGB32, GL_RGBA);

#undef NGL_TYPE_VALUE_MAP

NGL_END

namespace ngl = ::ngs::ngl;