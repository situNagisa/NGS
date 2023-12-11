#pragma once

#include "../../../tick_type.h"
#include "../defined.h"

NGS_OS_ESP_IO_BUS_BEGIN

struct NGS_DLL_API i2c_master : embedded::io::i2c::master
{
	NGS_MPL_ENVIRON(i2c_master);
public:
	i2c_master();
	virtual ~i2c_master() override;

	virtual bool is_opened() const override;
	virtual void close() override;

	virtual bool open(embedded::io::pin_t sda, embedded::io::pin_t scl, embedded::io::i2c::modes::address_t address) override;

	virtual void set_ack(embedded::io::i2c::modes::ack ack) override;
	virtual void set_address(embedded::io::i2c::modes::address mode) override;
	virtual void set_address(embedded::io::i2c::modes::address_t address) override;

	virtual size_t transfer(const embedded::io::i2c::message* messages, size_t count) override;

protected:
	esp_tick_type_t _wait = 1000.0f / portTICK_PERIOD_MS;
	i2c_port_t _port = -1;
	i2c_config_t _config{};
	i2c_cmd_handle_t _cmd = nullptr;
	struct
	{
		embedded::io::i2c::modes::address mode = embedded::io::i2c::modes::address::_7;
		embedded::io::i2c::modes::address_t value = embedded::io::i2c::modes::invalid_address;
	}_address{};
	embedded::io::i2c::modes::ack _ack = embedded::io::i2c::modes::ack::any;

};

NGS_OS_ESP_IO_BUS_END