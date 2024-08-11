#pragma once

#include "../defined.h"

NGS_OS_ESP_IO_BUS_BEGIN
namespace detail {
	inline constexpr size_t i2c_default_buffer_size = 512;
	inline allocators::id<I2C_NUM_MAX> i2c_ports;

	NGS_HPP_INLINE bool i2c_open_impl(
		embedded::io::pin_t sda, embedded::io::pin_t scl,
		i2c_port_t& port,
		i2c_config_t& config
	)
	{
		//data.cmd = i2c_cmd_link_create();

		config.sda_io_num = sda;
		config.scl_io_num = scl;
		config.sda_pullup_en = GPIO_PULLUP_ENABLE;
		config.scl_pullup_en = GPIO_PULLUP_ENABLE;
		config.clk_flags = I2C_SCLK_SRC_FLAG_FOR_NOMAL;

		port = i2c_ports.allocate();
		if (port == allocators::invalid_id) {
			//i2c_cmd_link_delete(data.cmd);
			NGS_LOGL(error, "port is full");
			return false;
		}

		esp_err_t ret = i2c_param_config(port, &config);
		NGS_OS_ESP_EXPECT_ERROR(ret);
		if (ret != ESP_OK) {
			i2c_ports.free(port);
			port = allocators::invalid_id;
			//i2c_cmd_link_delete(data.cmd);
			return false;
		}
		switch (config.mode)
		{
		case I2C_MODE_MASTER:
			NGS_OS_ESP_EXPECT_ERROR(ret = i2c_driver_install(port, config.mode, 0, 0, 0));
			if (ret != ESP_OK) {
				i2c_ports.free(port);
				port = allocators::invalid_id;
				//i2c_cmd_link_delete(data.cmd);
				return false;
			}
			break;
		case I2C_MODE_SLAVE:
			NGS_OS_ESP_EXPECT_ERROR(ret = i2c_driver_install(port, config.mode, i2c_default_buffer_size, i2c_default_buffer_size, 0));
			if (ret != ESP_OK) {
				i2c_ports.free(port);
				port = allocators::invalid_id;
				//i2c_cmd_link_delete(data.cmd);
				return false;
			}
			break;
		default:
			NGS_LOGL(error, "invalid mode:%d", config.mode);
			break;
		}
		return true;
	}

	NGS_HPP_INLINE void i2c_close_impl(i2c_port_t& port)
	{
		i2c_driver_delete(port);

		i2c_ports.free(port);
		port = allocators::invalid_id;
	}
}
NGS_OS_ESP_IO_BUS_END