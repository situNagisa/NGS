#pragma once

#include "./allocator.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

using owning_iic = resources::owning_view<iic_port>;

#ifndef portTICK_PERIOD_MS
constexpr auto port_tick_period_ms = 1;
#else
constexpr auto port_tick_period_ms = portTICK_PERIOD_MS;
#endif

NGS_LIB_MODULE_END