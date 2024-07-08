#pragma once

#include "./defined.h"

NGS_LIB_BEGIN

enum class code_bit
{
	compatibility = 0,
	long_mode = 1
};

enum class table_indicator
{
	global_descriptor_table = 0,
	local_descriptor_table = 1
};

enum class segment_type
{
	data,
	code,
	local_descriptor_table,
	task_state,
	gate,
};

enum class segment_descriptor_type
{
	system,
	code_or_data,
};

enum class gate
{
	call = 0b00,
	task = 0b01,
	interrupt = 0b10,
	trap = 0b11,
};

NGS_LIB_END