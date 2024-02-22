#pragma once

#include "../buffer.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

struct basic_indices : buffers::buffer<enums::buffer_target::element>
{
	NGS_MPL_ENVIRON(basic_indices);
public:

};

NGS_LIB_MODULE_END