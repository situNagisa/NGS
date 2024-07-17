#pragma once

#include "../defined.h"
#include "NGS/basic/basic.h"
#include "NGS/type_trait/type_trait.h"
#include "NGS/mpl/mstruct.h"
#include "NGS/static/string.h"
#include "NGS/external/stl/tuple.h"
#include "NGS/tcea/tcea.h"

#include "NGS/external/opengl_new/error.h"
#include "NGS/external/opengl_new/context.h"
#include "NGS/external/opengl_new/enum.h"


#define NGS_LIB_VERSION_MAJOR 0
#define NGS_LIB_VERSION_MINOR 1
#define NGS_LIB_VERSION_PATCH 0
#define NGS_LIB_NAME NGS_EXTERNAL_OPENGL_NS::buffers
#include "NGS/lib/lib.h"