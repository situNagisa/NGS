#pragma once

#include "./defined.h"
#include "./mode.h"
#include "../../frequency.h"

NGS_EMBEDDED_IO_BUS_SPI_BEGIN

struct NGS_DLL_API device
{
protected:
	using self_type = device;
public:
	virtual ~device() = default;

	virtual modes::polarity get_polarity()const = 0;
	virtual modes::phase get_phase()const = 0;
	virtual frequency_t get_frequency()const = 0;
	virtual pin_t get_cs()const = 0;
};

NGS_EMBEDDED_IO_BUS_SPI_END