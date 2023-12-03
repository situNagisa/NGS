#pragma once

#include "./defined.h"

NGS_LIB_BEGIN

struct instance_create_info
{
	vk::InstanceCreateFlags flags{};
	struct
	{
		std::string name{};
		uint32_t version{};
	}application{};
	struct
	{
		std::string name{};
		uint32_t version{};
	}engine{};
	uint32_t version{};

	std::vector<std::string> layers{};
	std::vector<std::string> extensions{};
};

NGS_LIB_END