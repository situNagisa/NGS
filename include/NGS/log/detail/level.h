#pragma once

#include "./defined.h"

NGS_LIB_MODULE_BEGIN

enum class level
{
	trace,
	debug,
	info,
	warn,
	error,
	fatal,
	max,
};

NGS_LIB_MODULE_END