#pragma once

#include "./defined.h"

NGS_LIB_MODULE_BEGIN

struct input_assembly
{
	enum class topology_type
	{
		point_list,
		line_list,
		line_strip,
		triangle_list,
		triangle_strip,
		triangle_fan,
		line_list_with_adjacency,
		line_strip_with_adjacency,
		triangle_list_with_adjacency,
		triangle_strip_with_adjacency,
		patch_list,
	};
	topology_type topology = topology_type::point_list;
	bool primitive_restart_enable = false;
};

NGS_LIB_MODULE_END