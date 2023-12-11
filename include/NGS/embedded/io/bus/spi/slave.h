#pragma once

#include "./spi.h"
#include "./mode.h"
#include "./device.h"

NGS_LIB_MODULE_BEGIN

struct NGS_DLL_API slave : basic_spi
{
	NGS_MPL_ENVIRON(slave);
public:
	virtual bool open(pin_t sclk, pin_t miso, pin_t mosi, pin_t cs) = 0;

	virtual pin_t get_cs()const = 0;
};

NGS_LIB_MODULE_END