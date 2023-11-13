#pragma once

#include "./master.h"
#include "./util.hpp"

NGS_OS_ESP_IO_BUS_BEGIN

NGS_HPP_INLINE master::master() = default;
NGS_HPP_INLINE master::~master()
{
	NGS_ASSERT(!is_open());
}

NGS_HPP_INLINE bool master::is_open() const
{
	return _port != allocators::invalid_id;
}

NGS_HPP_INLINE void master::close()
{
	NGS_ASSERT(is_open());
	detail::close_impl(_port);
	i2c_cmd_link_delete(_cmd);
}

NGS_HPP_INLINE bool master::open(
	embedded::io::pin_t sda, embedded::io::pin_t scl,
	embedded::io::bus::i2c::modes::address_t address)
{
	_config.mode = I2C_MODE_MASTER;
	_config.master.clk_speed = 400'000;

	return detail::open_impl(sda, scl, _port, _config);
}

NGS_HPP_INLINE void master::set_ack(embedded::io::bus::i2c::modes::ack ack)
{
	_ack = ack;
}

NGS_HPP_INLINE void master::set_address(embedded::io::bus::i2c::modes::address mode)
{
	_address.mode = mode;
}

NGS_HPP_INLINE void master::set_address(embedded::io::bus::i2c::modes::address_t address)
{
	_address.value = address;
}

NGS_HPP_INLINE size_t master::transfer(const embedded::io::bus::i2c::message* messages, size_t count)
{
	esp_err_t ret = ESP_OK;

	_cmd = i2c_cmd_link_create();

	for (size_t i = 0; i < count; i++)
	{
		auto& message = messages[i];

		i2c_master_start(_cmd);
		switch (message.io)
		{
		case embedded::io::bus::i2c::modes::io::read:
			i2c_master_write_byte(
				_cmd,
				embedded::io::bus::i2c::modes::read_address(_address.value),
				_ack != embedded::io::bus::i2c::modes::ack::none
			);
			i2c_master_read(
				_cmd,
				static_cast<uint8_t*>(message.read_buffer),
				message.size,
				static_cast<i2c_ack_type_t>(_ack)
			);
			break;
		case embedded::io::bus::i2c::modes::io::write:
			i2c_master_write_byte(
				_cmd,
				embedded::io::bus::i2c::modes::write_address(_address.value),
				_ack != embedded::io::bus::i2c::modes::ack::none
			);
			i2c_master_write(
				_cmd,
				static_cast<const uint8_t*>(message.write_buffer),
				message.size,
				_ack != embedded::io::bus::i2c::modes::ack::none
			);
			break;
		default:
			NGS_LOGL(error, "i2c unknown flag");
			break;
		}
	}
	i2c_master_stop(_cmd);
	ret = i2c_master_cmd_begin(_port, _cmd, _wait);
	i2c_cmd_link_delete(_cmd);
	//ret = i2c_master_write_to_device(iic.port, address, data, size, iic.ticks_to_wait / portTICK_PERIOD_MS);

	if (ret != ESP_OK) {
		if (ret == ESP_ERR_TIMEOUT)
			NGS_LOGL(warn, "iic master write data time out");
		else
			NGS_LOGL(error, "iic master write port:%d address %d ret=%003x", _port, _address, ret);
	}
	return ret == ESP_OK;
}

NGS_OS_ESP_IO_BUS_END
