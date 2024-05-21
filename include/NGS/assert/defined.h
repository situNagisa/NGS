#pragma once

#include "./config.h"

#include "NGS/basic/basic.h"
#include "NGS/location/location.h"
#include "NGS/static/string.h"

#if NGS_ASSERT_CONFIG_LOG_ENABLE
#include "NGS/log/log.h"
#endif

#if NGS_ASSERT_CONFIG_FORMAT_ENABLE
#include "NGS/fmt/fmt.h"
#endif

#define NGS_ASSERT_NS asserts

#define NGS_LIB_VERSION_MAJOR 0
#define NGS_LIB_VERSION_MINOR 1
#define NGS_LIB_VERSION_PATCH 1

#define NGS_LIB_NAME NGS_ASSERT_NS
#include "NGS/lib/lib.h"

