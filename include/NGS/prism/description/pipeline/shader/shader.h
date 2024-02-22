#pragma once

#include "./defined.h"

NGS_LIB_MODULE_BEGIN

enum class shader_stage
{
	vertex = 1ull << 0,
	tessellation_control = 1ull << 1,
	tessellation_evaluation = 1ull << 2,
	geometry = 1ull << 3,
	fragment = 1ull << 4,
	compute = 1ull << 5,
	all_graphics = vertex | tessellation_control | tessellation_evaluation | geometry | fragment,
	all = vertex | tessellation_control | tessellation_evaluation | geometry | fragment | compute,
};

using shader_stage_flag = flags::enum_flag<shader_stage>;

struct shader
{
	shader_stage_flag stage{};
	::std::string_view name{};
	::std::span<byte> code{};
};

NGS_LIB_MODULE_END