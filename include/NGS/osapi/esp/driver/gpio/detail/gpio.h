#pragma once

#include "./allocator.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

using owning_gpio = resources::owning_view<gpio_number>;

struct dynamic_gpio : owning_gpio
{
	NGS_PP_INJECT(dynamic_gpio);
public:
	using base_type::base_type;

	void set_level(ios::gpios::level l) const
	{
		auto result = ::gpio_set_level(base_type::base().value(), ::std::to_underlying(l));
		NGS_OSAPI_ESP_CHECK_ERROR_THROW_MESSAGE(result, "Failed to set GPIO level");
	}

	void set_direction(::gpio_mode_t mode) const
	{
		auto result = ::gpio_set_direction(base_type::base().value(), mode);
		NGS_OSAPI_ESP_CHECK_ERROR_THROW_MESSAGE(result, "Failed to set GPIO direction");
	}

	void reset() const
	{
		auto result = ::gpio_reset_pin(base_type::base().value());
		NGS_OSAPI_ESP_CHECK_ERROR_THROW_MESSAGE(result, "Failed to reset GPIO");
	}

	void set_pull_mode(::gpio_pull_mode_t pull_mode) const
	{
		auto result = ::gpio_set_pull_mode(base_type::base().value(), pull_mode);
		NGS_OSAPI_ESP_CHECK_ERROR_THROW_MESSAGE(result, "Failed to set GPIO pull mode");
	}

	void set_interrupt_type(::gpio_int_type_t interrupt_type) const
	{
		auto result = ::gpio_set_intr_type(base_type::base().value(), interrupt_type);
		NGS_OSAPI_ESP_CHECK_ERROR_THROW_MESSAGE(result, "Failed to set GPIO interrupt type");
	}

	void enable_interrupt() const
	{
		auto result = ::gpio_intr_enable(base_type::base().value());
		NGS_OSAPI_ESP_CHECK_ERROR_THROW_MESSAGE(result, "Failed to enable GPIO interrupt");
	}

	void disable_interrupt() const
	{
		auto result = ::gpio_intr_disable(base_type::base().value());
		NGS_OSAPI_ESP_CHECK_ERROR_THROW_MESSAGE(result, "Failed to disable GPIO interrupt");
	}
};

template<::gpio_mode_t Mode>
struct basic_gpio : owning_gpio
{
	NGS_PP_INJECT(basic_gpio);
public:
	constexpr static auto mode = Mode;

	explicit(false) basic_gpio(gpio_number&& number)
		: base_type(NGS_PP_PERFECT_FORWARD(number))
	{
		auto result = ::gpio_set_direction(base_type::base().value(), mode);
		NGS_OSAPI_ESP_CHECK_ERROR_THROW_MESSAGE(result, "Failed to set GPIO direction");
	}

	void set(ios::gpios::level level) const
		requires (static_cast<bool>(::std::to_underlying(mode) & GPIO_MODE_DEF_OUTPUT))
	{
		auto result = ::gpio_set_level(base_type::base().value(), ::std::to_underlying(level));
		NGS_OSAPI_ESP_CHECK_ERROR_THROW_MESSAGE(result, "Failed to set GPIO level");
	}

	auto pin_level() const
		requires (static_cast<bool>(::std::to_underlying(mode) & GPIO_MODE_DEF_INPUT))
	{
		return static_cast<ios::gpios::level>(::gpio_get_level(base_type::base().value()));
	}
};

using output_gpio = basic_gpio<::gpio_mode_t::GPIO_MODE_OUTPUT>;
using input_gpio = basic_gpio<::gpio_mode_t::GPIO_MODE_INPUT>;
using io_gpio = basic_gpio<::gpio_mode_t::GPIO_MODE_INPUT_OUTPUT>;

static_assert(ios::gpios::output_gpio<output_gpio>);
static_assert(ios::gpios::input_gpio<input_gpio>);
static_assert(ios::gpios::input_and_output_gpio<io_gpio>);


NGS_LIB_MODULE_END