#pragma once

#include "../defined.h"
#include "./esp_idf.h"
#include "NGS/bit/bit.h"
#include "NGS/symbol/symbol.h"
#include "NGS/allocator/allocator.h"

#define NGS_OS_ESP_BEGIN NGS_OS_BEGIN namespace esp{
#define NGS_OS_ESP_END } NGS_OS_END