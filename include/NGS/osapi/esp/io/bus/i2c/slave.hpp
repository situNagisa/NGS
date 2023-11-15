#pragma once

#include "./slave.h"
#include "./util.hpp"

NGS_OS_ESP_IO_BUS_BEGIN

NGS_HPP_INLINE slave::slave() = default;

NGS_HPP_INLINE slave::~slave()
{
	NGS_ASSERT(!is_open());
}

NGS_HPP_INLINE bool slave::is_open() const
{
	return _port != allocators::invalid_id;
}

NGS_HPP_INLINE void slave::close()
{
	NGS_ASSERT(is_open());
	detail::close_impl(_port);
}

NGS_HPP_INLINE bool slave::open(
	embedded::io::pin_t sda, embedded::io::pin_t scl,
	embedded::io::bus::i2c::modes::address_t address)
{
	_config.mode = I2C_MODE_SLAVE;
	_config.slave.addr_10bit_en = _address.mode == embedded::io::bus::i2c::modes::address::_10;
	_config.slave.slave_addr = _address.value;
	_config.slave.maximum_speed = 1'000'000;

	return detail::open_impl(sda, scl, _port, _config);
}

NGS_HPP_INLINE size_t slave::read(void_ptr buffer, size_t size)
{
#if defined(NGS_BUILD_TYPE_IS_DEBUG)
	auto ret = i2c_slave_read_buffer(_port, static_cast<uint8_t*>(buffer), size, _wait);
	if (ret == -1)
	{
		NGS_LOGL(warn, "i2c_slave_read_buffer failed");
		ret = 0;
	}
	return ret;
#else
	return i2c_slave_read_buffer(_port, static_cast<uint8_t*>(buffer), size, _wait);
#endif
}

NGS_HPP_INLINE size_t slave::write(void_ptr_cst buffer, size_t size)
{
#if defined(NGS_BUILD_TYPE_IS_DEBUG)
	auto ret = i2c_slave_write_buffer(_port, static_cast<const uint8_t*>(buffer), size, _wait);
	if (ret == -1)
	{
		NGS_LOGL(warn, "i2c_slave_write_buffer failed");
		ret = 0;
	}
	return ret;
#else
	return i2c_slave_write_buffer(_port, static_cast<const uint8_t*>(buffer), size, _wait);
#endif
}

NGS_HPP_INLINE void slave::set_address(embedded::io::bus::i2c::modes::address mode)
{
	_address.mode = mode;
}

NGS_HPP_INLINE void slave::set_address(embedded::io::bus::i2c::modes::address_t address)
{
	_address.value = address;
}


NGS_OS_ESP_IO_BUS_END
