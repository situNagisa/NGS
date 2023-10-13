#pragma once

#include "NGS/meta_struct/defined.h"

NGS_META_STRUCT_TYPE_BEGIN

struct NGS_API variable_d {
	size_t count;
	size_t size;
	size_t offset;
};

NGS_META_STRUCT_TYPE_END
