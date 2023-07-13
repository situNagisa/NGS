#pragma once

#include "NGS/ngl/defined.h"

#ifndef NGL_OPENGL_MAJOR
#define NGL_OPENGL_MAJOR 3
#endif

#ifndef NGL_OPENGL_MINOR
#define NGL_OPENGL_MINOR 3
#endif

#ifndef NGL_SHOW_GL_FUNC_MSG
#define NGL_SHOW_GL_FUNC(func) 
#else
#define NGL_SHOW_GL_FUNC(func) NGS_LOGL(debug,#func)
#endif
