#pragma once

#include "NGS/basic/basic.h"
#include "NGS/to_string/to_string.h"
#include "NGS/location/location.h"
#include "NGS/console/console.h"
#include "NGS/type_trait/type_trait.h"
#include "NGS/cpt/cpt.h"
#include "NGS/to_string/to_string.h"
#include "NGS/fmt/fmt.h"

#define NGS_LOG_BEGIN NGS_BEGIN namespace logs {
#define NGS_LOG_END } NGS_END


#include "NGS/basic/basic.h"

#define NGS_LIB_VERSION_MAJOR 0
#define NGS_LIB_VERSION_MINOR 1
#define NGS_LIB_VERSION_PATCH 0

#define NGS_LIB_NAME logs
#include "NGS/lib/lib.h"