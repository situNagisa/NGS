#pragma once

#include "./base.h"

NGS_CONSOLE_BEGIN

struct NGS_DLL_API default_console : console
{
private:
	using base_type = console;
public:
	using base_type::base_type;
	default_console() : base_type(0) {}
};

NGS_CONSOLE_END