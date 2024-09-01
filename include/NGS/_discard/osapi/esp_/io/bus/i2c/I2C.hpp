#pragma once

#include "NGS/esp/defined.h"
#include "NGS/esp/esp_idf.h"

NESP_BEGIN
_NGS_PRIV_BEGIN

inline constexpr size_t IIC_BUFFER_SIZE = 512;
inline ngs::NumberAllocator<I2C_NUM_MAX> s_i2c_ports;

using esp_tick_type_t = TickType_t;
constexpr float32 ms = 1.0f / portTICK_PERIOD_MS;

struct IICData {
	esp_tick_type_t ticks_to_wait;
	i2c_port_t port;
	i2c_config_t config;
	i2c_cmd_handle_t cmd;
};

NGS_END
NESP_END

NGS_HPP_INLINE ngs::I2C::I2C() {
	using namespace nesp::priv;

	NGS_NEW(_data, IICData);
	auto& data = *(IICData*)_data;

	data.port = -1;
	data.config = {};
	data.ticks_to_wait = 1 * ms;
}

NGS_HPP_INLINE ngs::I2C::~I2C()
{
	using namespace nesp::priv;

	auto& data = *(IICData*)_data;

	NGS_DELETE(&data);
}

//Open
NGS_HPP_INLINE bool ngs::I2C::Open(
	pin_t SDA,
	pin_t SCL,
	__address address
) {
	using namespace nesp::priv;

	auto& data = *(IICData*)_data;
	i2c_config_t& config = data.config;

	//data.cmd = i2c_cmd_link_create();

	config.sda_io_num = SDA;
	config.scl_io_num = SCL;
	config.sda_pullup_en = GPIO_PULLUP_ENABLE;
	config.scl_pullup_en = GPIO_PULLUP_ENABLE;
	config.clk_flags = I2C_SCLK_SRC_FLAG_FOR_NOMAL;

	data.port = s_i2c_ports.Allocate();
	if (data.port < 0) {
		//i2c_cmd_link_delete(data.cmd);
		NGS_LOGL(error, "port is full");
		return false;
	}
	NGS_LOGFL(debug, "port:%d", data.port);

	esp_err_t ret = i2c_param_config(data.port, &config);
	ESP_ERROR_CHECK_WITHOUT_ABORT(ret);
	if (ret != ESP_OK) {
		s_i2c_ports.Free(data.port);
		data.port = -1;
		//i2c_cmd_link_delete(data.cmd);
		return false;
	}
	if (config.mode == I2C_MODE_MASTER) {
		ESP_ERROR_CHECK_WITHOUT_ABORT(ret = i2c_driver_install(data.port, config.mode, 0, 0, 0));
		if (ret != ESP_OK) {
			s_i2c_ports.Free(data.port);
			data.port = -1;
			//i2c_cmd_link_delete(data.cmd);
			return false;
		}
	}
	else {
		ESP_ERROR_CHECK_WITHOUT_ABORT(ret = i2c_driver_install(data.port, config.mode, IIC_BUFFER_SIZE, IIC_BUFFER_SIZE, 0));
		if (ret != ESP_OK) {
			s_i2c_ports.Free(data.port);
			data.port = -1;
			//i2c_cmd_link_delete(data.cmd);
			return false;
		}
	}
	_address = address;
	NGS_LOGFL(debug, "SDA:%d,SCLK:%d address:%d success!", SDA, SCL, _address);
	return true;
}

NGS_HPP_INLINE void ngs::I2C::Close() {
	using namespace nesp::priv;

	auto& data = *(IICData*)_data;

	s_i2c_ports.Free(data.port);
	i2c_driver_delete(data.port);
	i2c_cmd_link_delete(data.cmd);

	data.port = -1;
	data.config = {};
	data.ticks_to_wait = 1000 / portTICK_PERIOD_MS;
}

NGS_HPP_INLINE bool ngs::I2C::IsOpened()const {
	using namespace nesp::priv;

	auto& data = *(IICData*)_data;
	return data.port >= 0;
}


NGS_HPP_INLINE bool ngs::I2CMaster::Open(
	pin_t SDA,
	pin_t SCL,
	__address address
) {
	using namespace nesp::priv;

	NGS_LOGL(debug, "open iic master");
	auto& data = *(IICData*)_data;
	i2c_config_t& config = data.config;

	config.mode = I2C_MODE_MASTER;
	config.master.clk_speed = 400'000;

	return __base::Open(SDA, SCL, address);
}

NGS_HPP_INLINE size_t ngs::I2CMaster::Transfer(const Message* messages, size_t count)
{
	using namespace nesp::priv;

	auto& iic = *(IICData*)_data;
	esp_err_t ret = ESP_OK;

	iic.cmd = i2c_cmd_link_create();

	for (size_t i = 0; i < count; i++)
	{
		auto& message = messages[i];

		i2c_master_start(iic.cmd);
		switch (message.flag)
		{
		case Flag::read:
			i2c_master_write_byte(iic.cmd, _AddressRead(), _ack.first);
			i2c_master_read(iic.cmd, reinterpret_cast<uint8_t*>(message.data.read), message.count, (i2c_ack_type_t)_ack.second);
			break;
		case Flag::write:
			i2c_master_write_byte(iic.cmd, _AddressWrite(), _ack.first);
			i2c_master_write(iic.cmd, reinterpret_cast<const uint8_t*>(message.data.write), message.count, _ack.first);
			break;
		default:
			NGS_LOGL(error, "i2c unknown flag");
			break;
		}
	}
	i2c_master_stop(iic.cmd);
	ret = i2c_master_cmd_begin(iic.port, iic.cmd, iic.ticks_to_wait);
	i2c_cmd_link_delete(iic.cmd);
	//ret = i2c_master_write_to_device(iic.port, address, data, size, iic.ticks_to_wait / portTICK_PERIOD_MS);

	if (ret != ESP_OK) {
		if (ret == ESP_ERR_TIMEOUT)
			NGS_LOGL(warning, "iic master write data time out");
		else
			NGS_LOGL(error, "iic master write port:%d address %d ret=%003x", iic.port, _address, ret);
	}
	return ret == ESP_OK;
}

NGS_HPP_INLINE bool ngs::I2CSlave::Open(
	pin_t SDA,
	pin_t SCL,
	__address address
) {
	using namespace nesp::priv;

	NGS_LOGL(debug, "open iic slave");
	auto& data = *(IICData*)_data;
	i2c_config_t& config = data.config;

	config.mode = I2C_MODE_SLAVE;
	config.slave.addr_10bit_en = 0;
	config.slave.slave_addr = address;
	config.slave.maximum_speed = 1'000'000;

	return __base::Open(SDA, SCL, address);
}

NGS_HPP_INLINE size_t ngs::I2CSlave::Write(
	ngs::byte_ptr_cst data,
	size_t size
) {
	using namespace nesp::priv;

	auto& iic = *(IICData*)_data;

#if NGS_BUILD_TYPE == NGS_DEBUG
	int length = i2c_slave_write_buffer(iic.port, data, size, iic.ticks_to_wait);
	if (length < 0)
		NGS_LOGFL(error, "iic slave write port:%d error:0x%0004x", iic.port, length);
	else if (!length)
		NGS_LOGL(warning, "iic slave had not written any data!");
	return length;
#else
	return i2c_slave_write_buffer(iic.port, data, size, iic.ticks_to_wait);
#endif
}

NGS_HPP_INLINE size_t ngs::I2CSlave::Read(
	ngs::byte_ptr data,
	size_t size
) {
	using namespace nesp::priv;
	auto& iic = *(IICData*)_data;

#if NGS_BUILD_TYPE == NGS_DEBUG
	auto result = i2c_slave_read_buffer(iic.port, data, size, iic.ticks_to_wait);
	if (result == -1)NGS_LOGL(warning, "i2c slave read buffer error");
	return 0;
#else
	return i2c_slave_read_buffer(iic.port, data, size, iic.ticks_to_wait);
#endif
}