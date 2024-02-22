#pragma once

#include "NGS/basic/basic.h"
#include "NGS/bases/bases.h"
#include "NGS/mpl/structure.h"
#include "NGS/tvm/tvm.h"
#include "NGS/cpt/cpt.h"
#include "NGS/type_trait/type_trait.h"
#include "NGS/external/boost/fusion.h"
#include "NGS/flag/flag.h"
#include "NGS/external/boost/stl_interfaces.h"
#include "NGS/prism/prism.h"

#include "./vulkan_api.h"

#define NGS_EXTERNAL_VULKAN_NS NGS_EXTERNAL_NS::vk

#define NGS_LIB_VERSION_MAJOR 0
#define NGS_LIB_VERSION_MINOR 1
#define NGS_LIB_VERSION_PATCH 0
#define NGS_LIB_NAME NGS_EXTERNAL_VULKAN_NS
#include "NGS/lib/lib.h"

