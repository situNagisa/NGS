#pragma once

#include "./entry.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

struct directory_entry : basic_entry
{
	NGS_PP_INJECT(directory_entry);
public:
	using base_type::base_type;
	using base_type::operator=;
};

NGS_LIB_MODULE_END