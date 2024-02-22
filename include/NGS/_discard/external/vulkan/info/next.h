#pragma once

#include "./environment.h"

NGS_LIB_MODULE_BEGIN

constexpr auto next(void_ptr_cst param)
{
	return[=](auto& info) -> auto & requires requires{ { info.pNext } -> ::std::assignable_from<void_ptr_cst>; }
	{
		info.pNext = param;
		return info;
	};
};

NGS_LIB_MODULE_END