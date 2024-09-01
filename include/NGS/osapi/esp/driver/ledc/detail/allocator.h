#pragma once

#include "./defined.h"

NGS_LIB_MODULE_BEGIN

using mode_allocator = allocators::unique_allocator<::ledc_mode_t>;
using mode_resource = mode_allocator::value_type;

using timer_allocator = allocators::unique_allocator<::ledc_timer_t>;
using timer_resource = timer_allocator::value_type;

using channel_allocator = allocators::unique_allocator<::ledc_channel_t>;
using channel_resource = channel_allocator::value_type;

using pin_allocator = allocators::unique_allocator<int>;
using pin_resource = pin_allocator::value_type;

constexpr auto make_full_mode_allocator() noexcept
{
	return mode_allocator(::std::views::iota(0, ::ledc_mode_t::LEDC_SPEED_MODE_MAX) | ::std::views::transform([](auto&& i) { return static_cast<::ledc_mode_t>(i); }));
}

constexpr auto make_full_timer_allocator() noexcept
{
	return timer_allocator(::std::views::iota(0, ::ledc_timer_t::LEDC_TIMER_MAX) | ::std::views::transform([](auto&& i) { return static_cast<::ledc_timer_t>(i); }));
}

constexpr auto make_full_channel_allocator() noexcept
{
	return channel_allocator(::std::views::iota(0, ::ledc_channel_t::LEDC_CHANNEL_MAX) | ::std::views::transform([](auto&& i) { return static_cast<::ledc_channel_t>(i); }));
}

constexpr auto make_full_pin_allocator() noexcept
{
	return pin_allocator(::std::views::iota(0, ::gpio_num_t::GPIO_NUM_MAX));
}

NGS_LIB_MODULE_END