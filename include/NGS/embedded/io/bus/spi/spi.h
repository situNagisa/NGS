#pragma once

#include "./defined.h"

NGS_LIB_MODULE_BEGIN

struct NGS_DLL_API basic_spi : basic_io
{
	NGS_MPL_ENVIRON(basic_spi);
public:

	virtual pin_t get_sclk()const = 0;
	virtual pin_t get_mosi()const = 0;
	virtual pin_t get_miso()const = 0;
};

NGS_LIB_MODULE_END