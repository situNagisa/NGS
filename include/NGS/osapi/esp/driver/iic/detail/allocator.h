#pragma once

#include "./defined.h"

NGS_LIB_MODULE_BEGIN

using allocator = allocators::unique_allocator<::i2c_port_t>;
using iic_port = allocator::value_type;

static_assert(resources::resource<iic_port>);

constexpr auto make_full_allocator()
{
	return allocator(::std::views::iota(0, ::i2c_port_t::I2C_NUM_MAX) | ::std::views::transform([](auto&& i) { return static_cast<::i2c_port_t>(i); }));
}

NGS_LIB_MODULE_END