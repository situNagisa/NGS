#pragma once

#include "./master.h"
#include "./util.hpp"

NGS_OS_ESP_IO_BUS_BEGIN

NGS_HPP_INLINE i2c_master::i2c_master() = default;
NGS_HPP_INLINE i2c_master::~i2c_master()
{
	NGS_ASSERT(!is_opened());
}

NGS_HPP_INLINE bool i2c_master::is_opened() const
{
	return _port != allocators::invalid_id;
}

NGS_HPP_INLINE void i2c_master::close()
{
	NGS_ASSERT(is_opened());
	detail::i2c_close_impl(_port);
	i2c_cmd_link_delete(_cmd);
}

NGS_HPP_INLINE bool i2c_master::open(
	embedded::io::pin_t sda, embedded::io::pin_t scl,
	embedded::io::i2c::modes::address_t address)
{
	_config.mode = I2C_MODE_MASTER;
	_config.master.clk_speed = 400'000;
	set_address(address);

	return detail::i2c_open_impl(sda, scl, _port, _config);
}

NGS_HPP_INLINE void i2c_master::set_ack(embedded::io::i2c::modes::ack ack)
{
	_ack = ack;
}

NGS_HPP_INLINE void i2c_master::set_address(embedded::io::i2c::modes::address mode)
{
	_address.mode = mode;
}

NGS_HPP_INLINE void i2c_master::set_address(embedded::io::i2c::modes::address_t address)
{
	_address.value = address;
}

NGS_HPP_INLINE size_t i2c_master::transfer(const embedded::io::i2c::message* messages, size_t count)
{
	_cmd = i2c_cmd_link_create();

	for (size_t i = 0; i < count; i++)
	{
		auto& message = messages[i];

		i2c_master_start(_cmd);
		switch (message.io)
		{
		case embedded::io::i2c::modes::io::read:
			i2c_master_write_byte(
				_cmd,
				embedded::io::i2c::modes::read_address(_address.value),
				_ack != embedded::io::i2c::modes::ack::none
			);
			i2c_master_read(
				_cmd,
				static_cast<uint8_t*>(message.read_buffer),
				message.size,
				static_cast<i2c_ack_type_t>(_ack)
			);
			break;
		case embedded::io::i2c::modes::io::write:
			i2c_master_write_byte(
				_cmd,
				embedded::io::i2c::modes::write_address(_address.value),
				_ack != embedded::io::i2c::modes::ack::none
			);
			i2c_master_write(
				_cmd,
				static_cast<const uint8_t*>(message.write_buffer),
				message.size,
				_ack != embedded::io::i2c::modes::ack::none
			);
			break;
		default:
			NGS_LOGL(error, "i2c unknown flag");
			break;
		}
	}
	i2c_master_stop(_cmd);
	esp_err_t result = 0;
	if (!NGS_OS_ESP_EXPECT_ERROR(
		result = i2c_master_cmd_begin(_port, _cmd, _wait),
		ngs::format("iic i2c_master write port:%d address:%d result:%d", _port, _address.value, result)
	)) {
		result = 0;
	}
	i2c_cmd_link_delete(_cmd);
	//ret = i2c_master_write_to_device(iic.port, address, data, size, iic.ticks_to_wait / portTICK_PERIOD_MS);

	return result;
}

NGS_OS_ESP_IO_BUS_END
