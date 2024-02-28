#pragma once

#include "NGS/basic/basic.h"
#include "NGS/ccpt/ccpt.h"
#include "NGS/layout/layout.h"
#include "NGS/static/string.h"
#include "NGS/type_trait/type_trait.h"
#include "NGS/cpt/cpt.h"
#include "NGS/to_string/to_string.h"
#include "NGS/mpl/template.h"
#include "NGS/assert/assert.h"
#include "NGS/bases/bases.h"

#include "NGS/external/boost/fusion.h"
#include "NGS/external/boost/stl_interfaces.h"

#include "../defined.h"

#define NGS_LIB_VERSION_MAJOR 2
#define NGS_LIB_VERSION_MINOR 0
#define NGS_LIB_VERSION_PATCH 0

#define NGS_LIB_NAME NGS_MPL_NS::mstruct
#include "NGS/lib/lib.h"