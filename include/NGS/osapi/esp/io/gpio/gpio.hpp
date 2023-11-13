#pragma once

#include "./gpio.h"

NGS_OS_ESP_IO_BEGIN

NGS_HPP_INLINE gpio::gpio() = default;

NGS_HPP_INLINE gpio::~gpio() = default;

NGS_HPP_INLINE bool gpio::open(embedded::io::pin_t gpio_num, embedded::io::gpio::modes::io io_mode)
{
	using namespace embedded::io::gpio;

	_data.pin = gpio_num;
	gpio_config_t& config = _data.config;

	config.pin_bit_mask = bits::scope(_data.pin);
	switch (io_mode)
	{
	case modes::io::input:
		config.mode = GPIO_MODE_INPUT;
		break;
	case modes::io::output:
		config.mode = GPIO_MODE_OUTPUT;
		break;
	default:
		break;
	}
	config.pull_up_en = GPIO_PULLUP_DISABLE;
	config.pull_down_en = GPIO_PULLDOWN_ENABLE;
	config.intr_type = GPIO_INTR_DISABLE;

	esp_err_t ret = gpio_config(&config);
	ESP_ERROR_CHECK_WITHOUT_ABORT(ret);
	if (ret != ESP_OK) {
		_data.pin = embedded::io::invalid_pin;
		return false;
	}
	NGS_LOGFL(debug, "%d success!", _data.pin);
	return true;
}

NGS_HPP_INLINE bool gpio::is_open() const
{
	return _data.pin != embedded::io::invalid_pin;
}

NGS_HPP_INLINE void gpio::close()
{

}

NGS_HPP_INLINE void gpio::reset()
{
	low();
}

NGS_HPP_INLINE void gpio::set_interrupt(bool enable)
{

}

NGS_HPP_INLINE void gpio::set_interrupt(embedded::io::gpio::modes::interrupt type)
{

}

NGS_HPP_INLINE void gpio::set_mode(embedded::io::gpio::modes::io mode)
{
	using namespace embedded::io::gpio;
	gpio_config_t& config = _data.config;

	switch (mode)
	{
	case modes::io::input:
		config.mode = GPIO_MODE_INPUT;
		break;
	case modes::io::output:
		config.mode = GPIO_MODE_OUTPUT;
		break;
	default:
		break;
	}
	ESP_ERROR_CHECK(gpio_config(&config));
}

NGS_HPP_INLINE void gpio::set(bool value)
{
	ESP_ERROR_CHECK(gpio_set_level(static_cast<gpio_num_t>(_data.pin), static_cast<uint32>(value)));
}

NGS_HPP_INLINE bool gpio::get() const
{
	return gpio_get_level(static_cast<gpio_num_t>(_data.pin));
}

NGS_OS_ESP_IO_END
