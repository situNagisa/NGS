#pragma once

#include "./defined.h"

NGS_LIB_MODULE_BEGIN

struct zero_reflecter
{
	using type = ::std::size_t;
	template<class>
	using reflect = ccpt::auto_constant < type{} > ;
};

NGS_LIB_MODULE_END