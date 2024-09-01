#pragma once

#include "./defined.h"

NGS_LIB_MODULE_BEGIN

using allocator = allocators::unique_allocator<::gpio_num_t>;
using gpio_number = allocator::value_type;

static_assert(resources::resource<gpio_number>);


NGS_LIB_MODULE_END