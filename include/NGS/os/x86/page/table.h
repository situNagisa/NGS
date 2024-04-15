#pragma once

#include "./entry.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

struct table_entry : basic_entry
{
	NGS_MPL_ENVIRON(table_entry);
public:
	using base_type::base_type;
	using base_type::operator=;
};

NGS_LIB_MODULE_END