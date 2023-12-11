#pragma once

#include "./defined.h"
#include "./mode.h"

NGS_LIB_MODULE_BEGIN

struct NGS_DLL_API basic_i2c : basic_io
{
	NGS_MPL_ENVIRON(basic_i2c);
public:
	virtual bool open(pin_t sda, pin_t scl, modes::address_t address) = 0;
	virtual bool open(pin_t sda, pin_t scl) { return open(sda, scl, modes::invalid_address); }

	virtual void set_address(modes::address mode) = 0;
	virtual void set_address(modes::address_t address) = 0;
};

NGS_LIB_MODULE_END