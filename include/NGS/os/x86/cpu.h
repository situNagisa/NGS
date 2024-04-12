#pragma once

#include "./segment.h"
#include "./defined.h"

NGS_LIB_BEGIN

struct cpu
{
	::std::span<segments::descriptor> global_descriptor_table;
};

NGS_LIB_END