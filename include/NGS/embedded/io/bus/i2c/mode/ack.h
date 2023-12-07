#pragma once

#include "./defined.h"

NGS_LIB_MODULE_BEGIN
namespace modes {

	enum class NGS_DLL_API ack
	{
		any = 0x0,			/*!< I2C ack for each byte read */
		none = 0x1,			/*!< I2C no ack for each byte read */
		last_no_ack = 0x2,	/*!< I2C no ack for the last byte*/
		max,
	};

}
NGS_LIB_MODULE_END