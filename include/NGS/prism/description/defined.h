#include "../defined.h"

#define NGS_PRISM_DESCRIPTION_NS descriptions
#define NGS_LIB_MODULE_NAME NGS_PRISM_DESCRIPTION_NS
#include "NGS/lib/module.h"

NGS_LIB_MODULE_BEGIN
using binding_type = uint32_t;
using stride_type = uint32_t;
using location_type = uint32_t;
using offset_type = uint32_t;
using size_type = uint32_t;
NGS_LIB_MODULE_END
