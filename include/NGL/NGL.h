#pragma once

#include "NGS/base/base.h"

#if NGS_PLATFORM == NGS_MSVC
#pragma warning(push)
#pragma warning(disable: 4244)
#pragma warning(push)
#pragma warning(disable: 4267)
#endif

#include "NGL/fw/glfw.h"

#include "NGL/gl/gl.h"

#include "NGL/api/shader.h"
#include "NGL/api/texture.h"
#include "NGL/api/vertex.h"
#include "NGL/api/vertex_array.h"
#include "NGL/api/renderer.h"

#if NGS_USE_HPP
#include "NGL/NGL.hpp"
#endif

#if NGS_PLATFORM == NGS_MSVC
#pragma warning(pop)
#pragma warning(pop)
#endif

#undef _NGL_DECALRE_CONTEXT
#undef _NGL_DECALRE_CURRENT
#undef _NGL_CURRENT_DEFAULT_CONSTRUCTOR
#undef _NGL_CURRENT_INSTANCE