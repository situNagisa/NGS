#pragma once

#include "./environment.h"

NGS_LIB_MODULE_BEGIN

constexpr auto type(const VkStructureType& param)
{
	return[=](auto& info) -> auto & requires requires{ { info.sType } -> ::std::assignable_from<VkStructureType>; }
	{
		info.sType = param;
		return info;
	};
};

NGS_LIB_MODULE_END
