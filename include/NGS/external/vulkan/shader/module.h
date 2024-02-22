#pragma once

#include "../basic.h"
#include "./defined.h"

NGS_EXTERNAL_VULKAN_REGISTER_MODULE(
	shader,
	VkShaderModuleCreateInfo,
	VkShaderModule,
	::vk::ShaderModuleCreateInfo::structureType,
	::vkCreateShaderModule,
	::vkDestroyShaderModule
);