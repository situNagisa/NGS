#pragma once

#include "./defined.h"
#include "./mode.h"

NGS_LIB_MODULE_BEGIN

struct NGS_DLL_API message
{
	modes::io io{};
	union
	{
		void_ptr_cst write_buffer = nullptr;
		void_ptr read_buffer;
	};
	size_t size = 0;
	void_ptr user_data = nullptr;
};

NGS_LIB_MODULE_END