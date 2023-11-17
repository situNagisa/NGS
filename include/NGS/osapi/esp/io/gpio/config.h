#pragma once

#include "../defined.h"

NGS_OS_ESP_IO_BEGIN

struct NGS_DLL_API gpio_config : gpio_config_t {

	constexpr void set_io(embedded::io::gpio::modes::io io_mode)
	{
		switch (io_mode)
		{
		case embedded::io::gpio::modes::io::disable:
			mode = GPIO_MODE_DISABLE;
			break;
		case embedded::io::gpio::modes::io::input:
			mode = GPIO_MODE_INPUT;
			break;
		case embedded::io::gpio::modes::io::input_output:
			mode = GPIO_MODE_INPUT_OUTPUT;
			break;
		case embedded::io::gpio::modes::io::input_output_open_drain:
			mode = GPIO_MODE_INPUT_OUTPUT_OD;
			break;
		case embedded::io::gpio::modes::io::output:
			mode = GPIO_MODE_OUTPUT;
			break;
		case embedded::io::gpio::modes::io::output_open_drain:
			mode = GPIO_MODE_OUTPUT_OD;
			break;
		default:

			break;
		}
	}

	constexpr void set_pull(embedded::io::gpio::modes::pull pull_mode)
	{
		switch (pull_mode)
		{
		case embedded::io::gpio::modes::pull::down:
			pull_up_en = GPIO_PULLUP_DISABLE;
			pull_down_en = GPIO_PULLDOWN_ENABLE;
			break;
		case embedded::io::gpio::modes::pull::up:
			pull_up_en = GPIO_PULLUP_ENABLE;
			pull_down_en = GPIO_PULLDOWN_DISABLE;
			break;
		case embedded::io::gpio::modes::pull::up_down:
			pull_up_en = GPIO_PULLUP_ENABLE;
			pull_up_en = GPIO_PULLUP_ENABLE;
			break;
		case embedded::io::gpio::modes::pull::floating:
			pull_up_en = GPIO_PULLUP_DISABLE;
			pull_down_en = GPIO_PULLDOWN_DISABLE;
			break;
		}
	}
};

NGS_OS_ESP_IO_END