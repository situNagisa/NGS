#pragma once

#include "./base.h"
#include "./message.h"

NGS_EMBEDDED_IO_BUS_I2C_BEGIN

struct NGS_DLL_API slave : basic_i2c
{
	NGS_MPL_ENVIRON(slave);
public:

};

NGS_EMBEDDED_IO_BUS_I2C_END