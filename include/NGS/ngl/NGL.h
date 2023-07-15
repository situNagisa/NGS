﻿#pragma once

#include "NGS/base/base.h"

#if NGS_PLATFORM == NGS_MSVC
#pragma warning(push)
#pragma warning(disable: 4244)
#pragma warning(push)
#pragma warning(disable: 4267)
#endif

#include "NGS/ngl/glfw.h"

#include "NGS/ngl/vertex/vertex.h"
#include "NGS/ngl/vertex/vertex_array.h"


#if NGS_USE_HPP
#include "NGS/ngl/NGL.hpp"
#endif

#if NGS_PLATFORM == NGS_MSVC
#pragma warning(pop)
#pragma warning(pop)
#endif

#undef _NGL_DECALRE_CONTEXT
#undef _NGL_DECALRE_CURRENT
#undef _NGL_CURRENT_DEFAULT_CONSTRUCTOR
#undef _NGL_CURRENT_INSTANCE