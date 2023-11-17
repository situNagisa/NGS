#pragma once

#include "./defined.h"

NGS_EMBEDDED_IO_BUS_SPI_BEGIN

struct NGS_DLL_API basic_spi : basic_bus
{
	NGS_MPL_ENVIRON(basic_spi);
public:

	virtual pin_t get_sclk()const = 0;
	virtual pin_t get_mosi()const = 0;
	virtual pin_t get_miso()const = 0;
};

NGS_EMBEDDED_IO_BUS_SPI_END