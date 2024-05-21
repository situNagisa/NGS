#pragma once

#include "./defined.h"

NGS_LIB_MODULE_BEGIN

enum class type
{
	data,
	code,
	ldt,
	tss,
	gate_call,
	gate_task,
	gate_interrupt,
	gate_trap,
};



NGS_LIB_MODULE_END