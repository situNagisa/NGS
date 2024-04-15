#pragma once

#include "./defined.h"

NGS_LIB_MODULE_BEGIN

struct data_segment
{
	NGS_MPL_ENVIRON_BEGIN(data_segment);
public:
	using underlying_type = ::std::uint16_t;

	union
	{
		underlying_type real;
		struct _on_protected_mode
		{
			underlying_type rpl : 2;
			underlying_type ti : 1;
			underlying_type index : 13;
		}protect;
	};
};

using code_segment = ::std::uint16_t;
using stack_segment = ::std::uint16_t;


NGS_LIB_MODULE_END