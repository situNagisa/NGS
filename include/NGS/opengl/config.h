#pragma once

#include "./defined.h"

#ifndef NGS_OPENGL_VERSION_MAJOR
#define NGS_OPENGL_VERSION_MAJOR 3
#endif

#ifndef NGS_OPENGL_VERSION_MINOR
#define NGS_OPENGL_VERSION_MINOR 3
#endif

#ifndef NGS_OPENGL_UNIFORM_MATRIX_TRANSPOSE
#define NGS_OPENGL_UNIFORM_MATRIX_TRANSPOSE GL_TRUE
#endif

#ifndef NGS_OPENGL_SHOW_GL_FUNC_MSG
#define NGS_OPENGL_SHOW_GL_FUNC(func) 
#else
#define NGS_OPENGL_SHOW_GL_FUNC(func) NGS_LOGL(debug,#func)
#endif
