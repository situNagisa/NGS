#pragma once

#include "./owning.h"
#include "./defined.h"


NGS_LIB_MODULE_BEGIN

#if CONFIG_SOC_I2C_SUPPORT_SLAVE

template<ios::iics::address_width Width>
struct esp_iic_slave : owning_iic
{
	NGS_PP_INJECT(esp_iic_slave);
public:
	constexpr static auto address_width = Width;

	esp_iic_slave(
		iic_port&& port,
		int scl,
		int sda,
		::std::uint16_t address,
		::std::uint32_t rx_buffer_size,
		::std::uint32_t tx_buffer_size,
		bool scl_pull_enable,
		bool sda_pull_enable
	)
		: base_type(::std::move(port))
	{
		::i2c_config_t config{
			.mode = ::I2C_MODE_SLAVE,
			.sda_io_num = sda,
			.scl_io_num = scl,
			.sda_pullup_en = sda_pull_enable,
			.scl_pullup_en = scl_pull_enable,
			.slave{
				.addr_10bit_en = Width == ios::iics::address_width::_10,
				.slave_addr = address,
			},
		};
		auto result = ::i2c_param_config(base_type::base().value(), &config);
		NGS_OSAPI_ESP_CHECK_ERROR_THROW_MESSAGE(result, "Failed to configure I2C slave");
		result = ::i2c_driver_install(base_type::base().value(), config.mode, rx_buffer_size, tx_buffer_size, 0);
		NGS_OSAPI_ESP_CHECK_ERROR_THROW_MESSAGE(result, "Failed to install I2C driver");
	}

	~esp_iic_slave()
	{
		if (base_type::base().valid())
		{
			auto result = ::i2c_driver_delete(base_type::base().value());
			NGS_OSAPI_ESP_CHECK_ERROR_THROW_MESSAGE(result, "Failed to delete I2C driver");
		}
	}

	void write(::std::span<const ::std::uint8_t> data, ::std::chrono::milliseconds timeout) const
	{
		auto result = ::i2c_slave_write_buffer(base_type::base().value(), data.data(), data.size(), timeout.count() / port_tick_period_ms);
		NGS_OSAPI_ESP_CHECK_ERROR_THROW_MESSAGE(result, "Failed to write to I2C slave");
	}
	void read(::std::span<::std::uint8_t> data, ::std::chrono::milliseconds timeout) const
	{
		auto result = ::i2c_slave_read_buffer(base_type::base().value(), data.data(), data.size(), timeout.count() / port_tick_period_ms);
		NGS_OSAPI_ESP_CHECK_ERROR_THROW_MESSAGE(result, "Failed to read from I2C slave");
	}
};

#endif

NGS_LIB_MODULE_END