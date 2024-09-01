#pragma once

#include "./esp_idf.h"

#include "NGS/basic/basic.h"
#include "NGS/assert/assert.h"
#include "NGS/location/location.h"
#include "NGS/resource/resource.h"
#include "NGS/allocator/allocator.h"

#include "NGS/osapi/esp/verify.h"

#include "../defined.h"

#define NGS_OSAPI_ESP_UART_NS uarts
#define NGS_LIB_VERSION_MAJOR 1
#define NGS_LIB_VERSION_MINOR 0
#define NGS_LIB_VERSION_PATCH 0
#define NGS_LIB_NAME NGS_OSAPI_ESP_DRIVER_NS::NGS_OSAPI_ESP_UART_NS
#include "NGS/lib/lib.h"
