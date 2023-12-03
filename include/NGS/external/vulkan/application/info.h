#pragma once

#include "./defined.h"

NGS_LIB_BEGIN

struct instance_create_info : VkInstanceCreateInfo
{
	using base_type = VkInstanceCreateInfo;

	constexpr instance_create_info() = default;
};

NGS_LIB_END