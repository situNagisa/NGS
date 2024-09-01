#pragma once

#include "../concept.h"
#include "./range.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

constexpr bool empty(box auto&& b)
{
	for (auto&& inter : b)
	{
		if (inter.empty())
			return true;
	}
	return false;
}

NGS_LIB_MODULE_END