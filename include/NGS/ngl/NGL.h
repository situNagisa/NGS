#pragma once

#define NGS_USE_NGL

#include "NGS/base/base.h"

#if NGS_PLATFORM == NGS_MSVC
#pragma warning(push)
#pragma warning(disable: 4244)
#pragma warning(push)
#pragma warning(disable: 4267)
#endif

#include "NGS/ngl/glfw.h"

//vertex
#include "NGS/ngl/vertex/vertex.h"
#include "NGS/ngl/vertex/indices.h"
#include "NGS/ngl/vertex/concepts.h"
#include "NGS/ngl/vertex/vertex_format.h"
#include "NGS/ngl/vertex/array/base.h"
#include "NGS/ngl/vertex/array/array.h"
#include "NGS/ngl/vertex/array/indices.h"
#include "NGS/ngl/vertex/array/polygon.h"
#include "NGS/ngl/vertex/array/line.h"

//shader
#include "NGS/ngl/shader/source.h"
#include "NGS/ngl/shader/shader.h"

//texture
#include "NGS/ngl/texture/texture.h"

//util
#include "NGS/ngl/utils/renderer.h"
#include "NGS/ngl/utils/camera.h"



#if NGS_USE_HPP
#include "NGS/ngl/NGL.hpp"
#endif

#if NGS_PLATFORM == NGS_MSVC
#pragma warning(pop)
#pragma warning(pop)
#endif