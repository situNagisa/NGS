#pragma once

#include "NGS/mpl/structure/defined.h"

NGS_STRUCTURE_TYPE_BEGIN

struct NGS_API variable_dynamic_data {
	size_t count;
	size_t size;
	size_t offset;
};

NGS_STRUCTURE_TYPE_END
