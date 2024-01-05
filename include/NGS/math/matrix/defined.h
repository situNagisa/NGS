#pragma once

#include "../defined.h"
#include "NGS/basic/basic.h"
#include "NGS/type_trait/type_trait.h"
#include "NGS/mpl/mpl.h"
#include "NGS/assert/assert.h"
#include "NGS/external/stl/range.h"
#include "NGS/external/boost/stl_interfaces.h"
#include "NGS/math/basic.h"
#include "NGS/cpt/cpt.h"
#include "NGS/to_string/to_string.h"
#include "NGS/math/vector.h"
#include "NGS/bases/bases.h"
#include "NGS/functional/binder.h"

#define NGS_MATH_MATRIX_NS NGS_MATH_NS::matrixes

#define NGS_LIB_VERSION_MAJOR 1
#define NGS_LIB_VERSION_MINOR 1
#define NGS_LIB_VERSION_PATCH 0
#define NGS_LIB_NAME NGS_MATH_MATRIX_NS
#include "NGS/lib/lib.h"
