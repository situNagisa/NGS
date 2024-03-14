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
#include "NGS/mpl/mstruct.h"
#include "NGS/fmt/fmt.h"
#include "NGS/symbol/symbol.h"

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
using pixel_internal_format_t = GLint;
using pixel_format_t = GLenum;
using gl_enum_t = GLenum;

NGS_LIB_END