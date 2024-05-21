#pragma once

#include "../../16.h"
#include "./register.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

//flags
struct flags_register : bit16::flags_register
{
	NGS_PP_INJECT(flags_register);
public:
	using underlying_type = register_underlying_t;
	using register_category_type = registers::eflags;

	base_type::underlying_type resume : 1;
	base_type::underlying_type visual_8086_mode : 1;
	base_type::underlying_type alignment_check_access_control : 1;
	base_type::underlying_type visual_interrupt : 1;

	base_type::underlying_type visual_interrupt_pending : 1;
	base_type::underlying_type identification : 1;
	base_type::underlying_type : 2;//0

	base_type::underlying_type : 8;//0
};

NGS_LIB_MODULE_END