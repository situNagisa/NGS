#pragma once

#include "./detail.h"
#include "./defined.h"

NGS_LIB_BEGIN

using details::mode_allocator;
using details::mode_resource;
using details::make_full_mode_allocator;
using details::channel_allocator;
using details::channel_resource;
using details::make_full_channel_allocator;
using details::timer_allocator;
using details::timer_resource;
using details::make_full_timer_allocator;
using details::pin_allocator;
using details::pin_resource;
using details::make_full_pin_allocator;

using details::ledc_channel;
using details::ledc_timer;
using details::state_timer;

using details::basic_ledc;
using details::make_ledc;

using details::duty_of;

NGS_LIB_END