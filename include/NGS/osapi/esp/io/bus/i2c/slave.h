#pragma once

#include "./tick_type.h"

NGS_OS_ESP_IO_BUS_BEGIN

struct NGS_DLL_API slave : embedded::io::bus::i2c::slave
{
	NGS_MPL_ENVIRON(slave);
public:
	slave();
	virtual ~slave() override;

	virtual bool is_open() const override;
	virtual void close() override;
	virtual bool open(embedded::io::pin_t sda, embedded::io::pin_t scl, embedded::io::bus::i2c::modes::address_t address) override;
	virtual size_t read(void_ptr buffer, size_t size) override;
	virtual size_t write(void_ptr_cst buffer, size_t size) override;
	virtual void set_address(embedded::io::bus::i2c::modes::address mode) override;
	virtual void set_address(embedded::io::bus::i2c::modes::address_t address) override;
protected:
	esp_tick_type_t _wait = 1.0f / portTICK_PERIOD_MS;
	i2c_port_t _port = -1;
	i2c_config_t _config{};
	struct
	{
		embedded::io::bus::i2c::modes::address mode = embedded::io::bus::i2c::modes::address::_7;
		embedded::io::bus::i2c::modes::address_t value = embedded::io::bus::i2c::modes::invalid_address;
	}_address{};

};

NGS_OS_ESP_IO_BUS_END