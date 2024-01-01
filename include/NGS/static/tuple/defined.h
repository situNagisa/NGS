#pragma once

#include "NGS/basic/basic.h"
#include "NGS/type_trait/type_trait.h"
#include "NGS/ccpt/ccpt.h"
#include "NGS/cpt/cpt.h"
#include "NGS/assert/assert.h"
#include "NGS/external/boost/fusion.h"

#include "../defined.h"

#define NGS_STATIC_TUPLE_NS NGS_STATIC_NS::tuples

#define NGS_LIB_VERSION_MAJOR 0
#define NGS_LIB_VERSION_MINOR 1
#define NGS_LIB_VERSION_PATCH 0
#define NGS_LIB_NAME NGS_STATIC_TUPLE_NS
#include "NGS/lib/lib.h"
