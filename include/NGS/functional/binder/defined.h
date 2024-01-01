#pragma once

#include "NGS/basic/basic.h"
#include "NGS/type_trait/type_trait.h"
#include "NGS/ccpt/ccpt.h"
#include "NGS/cpt/cpt.h"
#include "NGS/assert/assert.h"
#include "NGS/functional/parameter_packet.h"

#include "../defined.h"

#define NGS_FUNCTIONAL_BINDER_NS NGS_FUNCTIONAL_NS::binders

#define NGS_LIB_VERSION_MAJOR 0
#define NGS_LIB_VERSION_MINOR 1
#define NGS_LIB_VERSION_PATCH 0
#define NGS_LIB_NAME NGS_FUNCTIONAL_BINDER_NS
#include "NGS/lib/lib.h"
