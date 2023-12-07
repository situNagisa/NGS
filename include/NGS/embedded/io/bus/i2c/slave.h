#pragma once

#include "./base.h"
#include "./message.h"

NGS_LIB_MODULE_BEGIN

struct NGS_DLL_API slave : basic_i2c
{
	NGS_MPL_ENVIRON(slave);
public:

};

NGS_LIB_MODULE_END