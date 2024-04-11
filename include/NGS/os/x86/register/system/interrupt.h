#pragma once

#include "./span.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

struct interrupt_descriptor_table : _detail::basic_span_register
{
	NGS_MPL_ENVIRON(interrupt_descriptor_table);
public:
	
};

NGS_LIB_MODULE_END
