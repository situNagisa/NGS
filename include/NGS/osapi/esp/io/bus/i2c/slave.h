﻿#pragma once

#include "../../../tick_type.h"

NGS_OS_ESP_IO_BUS_BEGIN

struct NGS_DLL_API i2c_slave : embedded::io::i2c::slave
{
	NGS_MPL_ENVIRON(i2c_slave);
public:
	i2c_slave();
	virtual ~i2c_slave() override;

	virtual bool is_opened() const override;
	virtual void close() override;
	virtual bool open(embedded::io::pin_t sda, embedded::io::pin_t scl, embedded::io::i2c::modes::address_t address) override;
	using base_type::write;
	using base_type::read;
	virtual size_t read(void_ptr buffer, size_t size) override;
	virtual size_t write(void_ptr_cst buffer, size_t size) override;
	virtual void set_address(embedded::io::i2c::modes::address mode) override;
	virtual void set_address(embedded::io::i2c::modes::address_t address) override;
protected:
	esp_tick_type_t _wait = 1.0f / portTICK_PERIOD_MS;
	i2c_port_t _port = -1;
	i2c_config_t _config{};
	struct
	{
		embedded::io::i2c::modes::address mode = embedded::io::i2c::modes::address::_7;
		embedded::io::i2c::modes::address_t value = embedded::io::i2c::modes::invalid_address;
	}_address{};

};

NGS_OS_ESP_IO_BUS_END