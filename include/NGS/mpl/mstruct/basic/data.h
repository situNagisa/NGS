#pragma once

#include "../variable.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

struct NGS_DLL_API variable_data {
	::std::size_t size;
	::std::size_t offset;
	variables::variable_type_t type;
};

NGS_LIB_MODULE_END
