#pragma once

#include "../defined.h"

NGS_OS_ESP_IO_BEGIN

struct gpio_data {
	embedded::io::pin_t pin = embedded::io::invalid_pin;
	gpio_config_t config{};
};

NGS_OS_ESP_IO_END