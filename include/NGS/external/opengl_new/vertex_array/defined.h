#pragma once

#include "../defined.h"
#include "NGS/basic/basic.h"
#include "NGS/type_trait/type_trait.h"
#include "NGS/mpl/mstruct.h"
#include "NGS/static/string.h"
#include "NGS/tcea/tcea.h"
#include "NGS/concept/concept.h"
#include "NGS/external/stl/tuple.h"

#include "NGS/external/opengl_new/error.h"
#include "NGS/external/opengl_new/context.h"
#include "NGS/external/opengl_new/enum.h"
#include "NGS/external/opengl_new/reflect.h"
#include "NGS/external/opengl_new/uniform.h"
#include "NGS/external/opengl_new/buffer.h"
#include "NGS/external/opengl_new/indexer.h"


#define NGS_LIB_VERSION_MAJOR 0
#define NGS_LIB_VERSION_MINOR 1
#define NGS_LIB_VERSION_PATCH 0
#define NGS_LIB_NAME NGS_EXTERNAL_OPENGL_NS::vertex_arraies
#include "NGS/lib/lib.h"