#pragma once

#include "./defined.h"
#include "./mode.h"

NGS_EMBEDDED_IO_BUS_I2C_BEGIN

struct NGS_DLL_API basic_i2c : basic_bus
{
	NGS_MPL_ENVIRON(basic_i2c);
public:
	virtual ~basic_i2c() override = default;

	virtual bool open(pin_t sda, pin_t scl, modes::address_t address) = 0;
	virtual bool open(pin_t sda, pin_t scl) { return open(sda, scl, modes::invalid_address); }

	virtual void set_address(modes::address mode) = 0;
	virtual void set_address(modes::address_t address) = 0;
};

NGS_EMBEDDED_IO_BUS_I2C_END