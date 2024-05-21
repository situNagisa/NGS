#pragma once

#include "./defined.h"

NGS_LIB_MODULE_BEGIN

//ds
struct data_segment
{
	NGS_PP_INJECT_BEGIN(data_segment);
public:
	using underlying_type = ::std::uint16_t;

	union
	{
		underlying_type real;
		struct _on_protected_mode
		{
			underlying_type requested_privilege : 2;
			underlying_type table_indicator : 1;
			underlying_type index : 13;
		}protect;
	};
};

//cs
using code_segment = ::std::uint16_t;
//ss
using stack_segment = ::std::uint16_t;
//es
using extra_segment = ::std::uint16_t;
//fs
using more_extra_segment = ::std::uint16_t;
//gs
using yet_more_extra_segment = ::std::uint16_t;


NGS_LIB_MODULE_END