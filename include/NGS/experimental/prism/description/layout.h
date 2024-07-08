#pragma once

#include "./descriptor.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

struct pipeline_layout
{

	struct push_constant_type
	{
		shader_stage_flag stage{};
		offset_type offset = 0;
		size_type size = 0;
	};

	::std::span<push_constant_type> push_constants{};
};

NGS_LIB_MODULE_END