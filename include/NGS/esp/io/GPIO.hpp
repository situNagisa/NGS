#pragma once

#include "NGS/esp/defined.h"
#include "NGS/esp/esp_idf.h"

NESP_BEGIN
_NGS_PRIV_BEGIN

struct GPIOData {
	pin_t pin;
	gpio_config_t config;
};

NGS_END
NESP_END


NGS_BEGIN

NGS_HPP_INLINE bool GPIO::Open(pin_t pin, GPIO::Mode mode) {
	using namespace esp::priv;

	NGS_NEW(_data, GPIOData);
	auto& data = *(GPIOData*)_data;
	data.pin = pin;
	gpio_config_t& config = data.config;

	config.pin_bit_mask = bit::scope(pin);
	switch (mode)
	{
	case GPIO::Mode::input:
		config.mode = GPIO_MODE_INPUT;
		break;
	case GPIO::Mode::output:
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
		NGS_DELETE(&data);
		_data = nullptr;
		return false;
	}
	NGS_LOGFL(debug, "%d success!", pin);
	return true;
}

NGS_HPP_INLINE bool GPIO::IsOpened()const { return _data; }
NGS_HPP_INLINE void GPIO::Close() {
	using namespace esp::priv;

	GPIOData& data = *(GPIOData*)_data;

	NGS_DELETE(&data);
	_data = nullptr;
}

NGS_HPP_INLINE void GPIO::Reset() {
	using namespace esp::priv;
}

NGS_HPP_INLINE void GPIO::SetInterrupt(bool enable) {
	using namespace esp::priv;
}
NGS_HPP_INLINE void GPIO::SetInterrupt(GPIO::Interrupt type) {
	using namespace esp::priv;
}

NGS_HPP_INLINE void GPIO::SetMode(GPIO::Mode mode) {
	using namespace esp::priv;

	auto& data = *(GPIOData*)_data;
	gpio_config_t& config = data.config;

	switch (mode)
	{
	case GPIO::Mode::input:
		config.mode = GPIO_MODE_INPUT;
		break;
	case GPIO::Mode::output:
		config.mode = GPIO_MODE_OUTPUT;
		break;
	default:
		break;
	}
	ESP_ERROR_CHECK(gpio_config(&config));
}

NGS_HPP_INLINE bool GPIO::Get()const {
	using namespace esp::priv;

	auto& data = *(GPIOData*)_data;
	return gpio_get_level((gpio_num_t)data.pin);
}

NGS_HPP_INLINE void GPIO::Set(bool level) {
	using namespace esp::priv;

	auto& data = *(GPIOData*)_data;
	ESP_ERROR_CHECK(gpio_set_level((gpio_num_t)data.pin, (uint32)level));
}

NGS_END
