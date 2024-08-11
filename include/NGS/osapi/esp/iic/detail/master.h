#pragma once

#include "./owning.h"
#include "./command.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

struct esp_iic_master : owning_iic
{
	NGS_PP_INJECT(esp_iic_master);
public:
	esp_iic_master(
		iic_port&& port,
		int scl,
		int sda,
		::std::uint32_t frequency,
		bool scl_pull_enable,
		bool sda_pull_enable,
		::std::uint32_t clock_flags = I2C_SCLK_SRC_FLAG_FOR_NOMAL
	)
		: base_type(::std::move(port))
	{
		::i2c_config_t config{
			.mode = ::I2C_MODE_MASTER,
			.sda_io_num = sda,
			.scl_io_num = scl,
			.sda_pullup_en = sda_pull_enable,
			.scl_pullup_en = scl_pull_enable,
			.master{
				.clk_speed = frequency
				},
			.clk_flags = clock_flags,
		};
		using namespace ::std::string_literals;
		auto result = ::i2c_param_config(base_type::base().value(), &config);
		NGS_OSAPI_ESP_CHECK_ERROR_THROW_MESSAGE(result, "Failed to configure I2C master");
		result = ::i2c_driver_install(base_type::base().value(), config.mode, 0, 0, 0);
		NGS_OSAPI_ESP_CHECK_ERROR_THROW_MESSAGE(result, "Failed to install I2C driver");
	}
	esp_iic_master(self_type&& other)noexcept
		: base_type(::std::move(other))
	{
	}
	self_type& operator=(self_type&& other)noexcept
	{
		if (this == &other)
			return *this;
		_release();
		base_type::operator=(::std::move(other));
		other._release();
		return *this;
	}

	~esp_iic_master()
	{
		_release();
	}

	void _release() noexcept
	{
		if (!base_type::base().valid())
			return;
		auto result = ::i2c_driver_delete(base_type::base().value());
		NGS_OSAPI_ESP_CHECK_ERROR_THROW_MESSAGE(result, "Failed to delete I2C driver");
	}

	void cmd_begin(command_link& link, ::std::chrono::milliseconds timeout = ::std::chrono::milliseconds(0)) const
	{
		auto result = ::i2c_master_cmd_begin(base_type::base().value(), link.handle(), timeout.count() / port_tick_period_ms);
		NGS_OSAPI_ESP_CHECK_ERROR_THROW_MESSAGE(result, "Failed to begin I2C command");
	}

	void reset_transfer_fifo() const
	{
		auto result = ::i2c_reset_tx_fifo(base_type::base().value());
		NGS_OSAPI_ESP_CHECK_ERROR_THROW_MESSAGE(result, "Failed to reset I2C transfer FIFO");
	}
	void reset_receive_fifo() const
	{
		auto result = ::i2c_reset_rx_fifo(base_type::base().value());
		NGS_OSAPI_ESP_CHECK_ERROR_THROW_MESSAGE(result, "Failed to reset I2C receive FIFO");
	}

	void write(
		::std::uint8_t address, 
		::std::span<const ::std::uint8_t> data, 
		::std::chrono::milliseconds timeout = ::std::chrono::milliseconds(0)
	) const
	{
		auto result = ::i2c_master_write_to_device(
			base_type::base().value(),
			//ios::iics::address_cast<ios::iics::address_width::_7, ios::iics::address_io::write>(static_cast<::std::uint8_t>(address << 1)),
			address,
			data.data(), 
			data.size(), 
			timeout.count() / port_tick_period_ms
		);
		NGS_OSAPI_ESP_CHECK_ERROR_THROW_MESSAGE(result, ::std::format("Failed to write to I2C device({:#02x})", address));
	}

	void read(::std::uint8_t address, ::std::span<::std::uint8_t> data, ::std::chrono::milliseconds timeout = ::std::chrono::milliseconds(0)) const
	{
		auto result = ::i2c_master_read_from_device(
			base_type::base().value(),
			//ios::iics::address_cast<ios::iics::address_width::_7, ios::iics::address_io::read>(static_cast<::std::uint8_t>(address << 1)),
			address,
			data.data(),
			data.size(),
			timeout.count() / port_tick_period_ms
		);
		NGS_OSAPI_ESP_CHECK_ERROR_THROW_MESSAGE(result, ::std::format("Failed to read from I2C device({:#02x})", address));
	}

	void write_read(
		::std::uint8_t address,
		::std::span<const ::std::uint8_t> write_data,
		::std::span<::std::uint8_t> read_data,
		::std::chrono::milliseconds timeout = ::std::chrono::milliseconds(0)
	) const
	{
		auto result = ::i2c_master_write_read_device(
			base_type::base().value(),
			//ios::iics::address_cast<ios::iics::address_width::_7, ios::iics::address_io::write>(static_cast<::std::uint8_t>(address << 1)),
			address,
			write_data.data(),
			write_data.size(),
			read_data.data(),
			read_data.size(),
			timeout.count() / port_tick_period_ms
		);
		NGS_OSAPI_ESP_CHECK_ERROR_THROW_MESSAGE(result, ::std::format("Failed to write and read from I2C device({:#02x})", address));
	}
};

NGS_LIB_MODULE_END