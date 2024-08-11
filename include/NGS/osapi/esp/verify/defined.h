#pragma once

#include "./esp_idf.h"

#include "NGS/basic/basic.h"
#include "NGS/assert/assert.h"
#include "NGS/location/location.h"

#include "../defined.h"

#define NGS_OSAPI_ESP_VERIFY_NS verfies
#define NGS_LIB_VERSION_MAJOR 1
#define NGS_LIB_VERSION_MINOR 0
#define NGS_LIB_VERSION_PATCH 0
#define NGS_LIB_NAME NGS_OSAPI_ESP_NS::NGS_OSAPI_ESP_VERIFY_NS
#include "NGS/lib/lib.h"
