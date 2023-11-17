#pragma once

#include "./spi.h"
#include "./device.h"

NGS_EMBEDDED_IO_BUS_SPI_BEGIN

struct NGS_DLL_API master : basic_spi
{
	NGS_MPL_ENVIRON(master);
public:
	virtual bool open(pin_t sclk, pin_t miso, pin_t mosi) = 0;
	virtual void select(const device& device) = 0;
	virtual void add_device(const device& device) = 0;
	virtual void remove_device(const device& device) = 0;
	virtual const device* get_current_device() const = 0;
	//virtual void lock() = 0;
	//virtual void unlock() = 0;
};

NGS_EMBEDDED_IO_BUS_SPI_END