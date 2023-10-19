#pragma once

#include "./concept.h"
#include "../attrib/dynamic_data.h"

NGS_NGL_FUSION_BEGIN

struct buffer_dynamic_data {
	size_t count;
	size_t size;
	std::vector<attrib_dynamic_data> properties;
};

NGS_NGL_FUSION_END
