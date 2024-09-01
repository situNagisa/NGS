#pragma once

#include "./allocator.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

using owning_uart = resources::owning_view<uart_port>;

NGS_LIB_MODULE_END