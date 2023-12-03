#pragma once

#include "./concept.h"

NGS_NGL_FUSION_BEGIN

struct attrib_dynamic_data : mpl::mstruct::variable_dynamic_data {
	type_t type;

	bool normalized;
};

NGS_NGL_FUSION_END
