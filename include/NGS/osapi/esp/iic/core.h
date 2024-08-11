#pragma once

#include "./detail.h"
#include "./defined.h"

NGS_LIB_BEGIN

using details::allocator;
using details::make_full_allocator;
using details::iic_port;

using details::command_link;
using details::static_command_link;
using details::owning_iic;
using details::esp_iic_master;
#if CONFIG_SOC_I2C_SUPPORT_SLAVE
using details::esp_iic_slave;
#endif


NGS_LIB_END