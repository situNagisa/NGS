#pragma once

#include "./defined.h"

NGS_LIB_MODULE_BEGIN

using allocator = allocators::unique_allocator<::uart_port_t>;
using uart_port = allocator::value_type;

static_assert(resources::resource<uart_port>);

constexpr auto make_full_allocator()
{
	return allocator(::std::views::iota(0, ::uart_port_t::UART_NUM_MAX) | ::std::views::transform([](auto&& i) { return static_cast<::uart_port_t>(i); }));
}

NGS_LIB_MODULE_END