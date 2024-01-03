#pragma once

#include "NGS/nsl/defined.h"
#include "NGS/nsl/depend.h"
#include "NGS/nsl/file/device_file.h"

NSL_BEGIN
_NGS_PRIV_BEGIN

constexpr auto i2c_master_path = "/dev/ngs_i2c_master";
constexpr auto i2c_slave_path = "/dev/ngs_i2c_slave";

struct IICData {
	DeviceFile i2c;
	pin_t sda;
	pin_t sclk;
};

NGS_END
NSL_END

NGS_HPP_INLINE ngs::I2C::I2C() {
	using namespace nsl::priv;

	NGS_NEW(_data, IICData);
	auto& data = *(IICData*)_data;
}

NGS_HPP_INLINE ngs::I2C::~I2C()
{
	using namespace nsl::priv;

	auto& data = *(IICData*)_data;

	NGS_DELETE(&data);
}

//Open
NGS_HPP_INLINE bool ngs::I2C::Open(
	pin_t SDA,
	pin_t SCL,
	__address address
) {
	using namespace nsl::priv;

	auto& data = *(IICData*)_data;
	
	data.sda = SDA;
	data.sclk = SCL;

	_address = address;
	NGS_LOGFL(debug, "SDA:%d,SCLK:%d address:%d success!", SDA, SCL, _address);
	return true;
}

NGS_HPP_INLINE void ngs::I2C::Close() {
	using namespace nsl::priv;

	auto& data = *(IICData*)_data;

	data.sda = -1;
	data.sclk = -1;
	_address = null_address;
	data.i2c.Close();
}

NGS_HPP_INLINE bool ngs::I2C::IsOpened()const {
	using namespace nsl::priv;

	auto& data = *(IICData*)_data;
	return data.i2c.IsOpened();
}


NGS_HPP_INLINE bool ngs::I2CMaster::Open(
	pin_t SDA,
	pin_t SCL,
	__address address
) {
	using namespace nsl::priv;

	auto& data = *(IICData*)_data;
	
	if (!data.i2c.IsOpened() && !data.i2c.Open(i2c_master_path)) {
		NGS_LOGFL(error, "can't find i2c device on path %s,please compile NGS/nsl/linux/driver/i2c.c and put it on %s", i2c_master_path, i2c_master_path);
		return false;
	}

	return __base::Open(SDA, SCL, address);
}

NGS_HPP_INLINE size_t ngs::I2CMaster::Transfer(const Message* messages, size_t count)
{
	using namespace nsl::priv;

	auto& i2c = *(IICData*)_data;
	constexpr auto convert_to_linux_i2c_msg = [](const Message& message,uint16 address)->i2c_msg {
		return i2c_msg{
			.addr = address,
			.flags = (uint16)message.flag,
			.len = (uint16)message.count,
			.buf = (byte_ptr)message.data.write
		};
	};
	auto trans_data = new i2c_msg[count]();
	for (size_t i = 0; i < count; i++)
	{
		auto& message = messages[i];
		trans_data[i] = convert_to_linux_i2c_msg(message, _address);
	}
	auto ret = i2c.i2c.Write((byte_ptr)trans_data, count * sizeof(i2c_msg));


	delete trans_data;
	trans_data = nullptr;
	
	return ret;
}

NGS_HPP_INLINE bool ngs::I2CSlave::Open(
	pin_t SDA,
	pin_t SCL,
	__address address
) {
	using namespace nsl::priv;

	auto& data = *(IICData*)_data;

	if (!data.i2c.IsOpened() && !data.i2c.Open(i2c_slave_path)) {
		NGS_LOGFL(error, "can't find i2c device on path %s,please compile NGS/nsl/linux/driver/i2c.c and put it on %s", i2c_slave_path, i2c_slave_path);
		return false;
	}

	return __base::Open(SDA, SCL, address);
}

NGS_HPP_INLINE size_t ngs::I2CSlave::Write(
	ngs::byte_ptr_cst data,
	size_t size
) {
	using namespace nsl::priv;

	auto& iic = *(IICData*)_data;

	return 0;
}

NGS_HPP_INLINE size_t ngs::I2CSlave::Read(
	ngs::byte_ptr data,
	size_t size
) {
	using namespace nsl::priv;
	auto& iic = *(IICData*)_data;

	return 0;
}