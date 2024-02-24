#pragma once

#include "../defined.h"
#include "NGS/basic/basic.h"
#include "NGS/cpt/cpt.h"
#include "NGS/bases/bases.h"
#include "NGS/assert/assert.h"
#include "NGS/type_trait/type_trait.h"
#include "NGS/log/log.h"
#include "NGS/external/stl/tuple.h"
#include "NGS/color/color.h"
#include "NGS/mpl/structure.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define NGS_EXTERNAL_OPENGL_NS opengl

#define NGS_LIB_VERSION_MAJOR 0
#define NGS_LIB_VERSION_MINOR 1
#define NGS_LIB_VERSION_PATCH 0

#define NGS_LIB_NAME NGS_EXTERNAL_NS::NGS_EXTERNAL_OPENGL_NS
#include "NGS/lib/lib.h"

NGS_LIB_BEGIN

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

NGS_DEFINE_TV(gl, fundamental_t, colors::primaries::RGBA24, GL_RGB);
NGS_DEFINE_TV(gl, fundamental_t, colors::primaries::RGBA32, GL_RGBA);

NGS_LIB_END