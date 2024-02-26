#pragma once

#include "./concept.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

constexpr auto operator<=>(const align auto& left,const align auto& right)
{
	return left.priority() <=> right.priority();
}

constexpr bool operator==(const align auto& left, const align auto& right)
{
	return (left <=> right) == 0;
}

NGS_LIB_MODULE_END