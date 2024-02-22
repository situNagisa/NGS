#pragma once

#include "../defined.h"
#include "../assert.h"
#include "NGS/embedded/embedded.h"
#include "NGS/bit/bit.h"
#include "NGS/symbol/symbol.h"
#include "NGS/to_string/to_string.h"
#include "NGS/allocator/allocator.h"
#include "NGS/bases/bases.h"
#include "NGS/fmt/fmt.h"

#define NGS_OS_ESP_IO_BEGIN NGS_OS_ESP_BEGIN namespace io{
#define NGS_OS_ESP_IO_END } NGS_OS_ESP_END