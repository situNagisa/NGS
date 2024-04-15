#pragma once

#include "./defined.h"

NGS_LIB_MODULE_BEGIN

struct control_0
{
	bool protected_enable;
	bool monitor_coprocessor;
	bool emulation;
	bool task_switched;
	bool extension_type;
	bool numeric_error;
	bool write_protect;
	bool alignment_mask;
	bool not_write_through;
	bool cache_disable;
	bool paging;
};

NGS_LIB_MODULE_END