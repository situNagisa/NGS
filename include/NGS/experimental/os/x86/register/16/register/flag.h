#pragma once

#include "../register.h"
#include "./register.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

//flags
struct flags_register
{
	NGS_PP_INJECT_BEGIN(flags_register);
public:
	using underlying_type = register_underlying_t;
	using register_category_type = tags::flags;

	underlying_type carry : 1;
	underlying_type : 1;//1
	underlying_type parity : 1;
	underlying_type : 1;//0

	underlying_type auxiliary_carry : 1;
	underlying_type : 1;//0
	underlying_type zero : 1;
	underlying_type sign : 1;

	underlying_type trap : 1;
	underlying_type interruptible : 1;
	underlying_type direction : 1;
	underlying_type overflow : 1;

	underlying_type io_privilege : 2;
	underlying_type nested_task : 1;
	underlying_type : 1;//0
};

NGS_LIB_MODULE_END