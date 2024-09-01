#pragma once

#include "./gpio.h"

NGS_OS_ESP_IO_BEGIN

NGS_HPP_INLINE gpio::gpio() = default;

NGS_HPP_INLINE gpio::~gpio() = default;

NGS_HPP_INLINE bool gpio::open(embedded::io::pin_t gpio_num, embedded::io::gpio::modes::io io_mode, embedded::io::gpio::modes::pull pull_mode)
{
	using namespace embedded::io::gpio;

	_config.set_io(io_mode);
	_config.set_pull(pull_mode);
	return open(gpio_num, _config);
}

NGS_HPP_INLINE bool gpio::is_opened() const
{
	return _pin != embedded::io::invalid_pin;
}

NGS_HPP_INLINE void gpio::close()
{
	reset();
	_pin = embedded::io::invalid_pin;
}

NGS_HPP_INLINE void gpio::reset()
{
	gpio_config config{};
	config.pin_bit_mask = _config.pin_bit_mask;
	NGS_OS_ESP_ASSERT_ERROR(::gpio_config(&config), fmt::c("io num = %d", _pin));
}

NGS_HPP_INLINE void gpio::set_interrupt(bool enable)
{

}

NGS_HPP_INLINE void gpio::set_interrupt(embedded::io::gpio::modes::interrupt type)
{

}

NGS_HPP_INLINE void gpio::set_io(embedded::io::gpio::modes::io mode)
{
	_config.set_io(mode);
	NGS_OS_ESP_ASSERT_ERROR(::gpio_config(&_config), fmt::c("io num = %d, io mode = 0x%02x", _pin, mode));
}

NGS_HPP_INLINE void gpio::set_pull(embedded::io::gpio::modes::pull mode)
{
	_config.set_pull(mode);
	NGS_OS_ESP_ASSERT_ERROR(::gpio_config(&_config), fmt::c("io num = %d, pull mode = %d", _pin, mode));
}

NGS_HPP_INLINE void gpio::set(bool value)
{
	//NGS_LOGFL(debug, "io num = %d, level = %s", _pin, ngs::to_string(value).data());
	NGS_OS_ESP_ASSERT_ERROR(::gpio_set_level(static_cast<gpio_num_t>(_pin), static_cast<uint32>(value)), fmt::c("io num = %d, level = %s", _pin, to_strings::to_string(value).data()));
}

NGS_HPP_INLINE bool gpio::get() const
{
	return ::gpio_get_level(static_cast<gpio_num_t>(_pin));
}

NGS_HPP_INLINE bool gpio::open(embedded::io::pin_t gpio_num, const gpio_config& config)
{
	_pin = gpio_num;
	_config = config;
	_config.pin_bit_mask = bits::scope(gpio_num);

	if (!NGS_OS_ESP_EXPECT_ERROR(::gpio_config(&_config), fmt::c("io num = %d", _pin))) {
		_pin = embedded::io::invalid_pin;
		return false;
	}
	return true;
}

NGS_OS_ESP_IO_END
