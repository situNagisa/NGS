#pragma once

#include "../basic.h"
#include "./defined.h"

NGS_EXTERNAL_VULKAN_REGISTER_MODULE(
	pipeline_layouts,
	VkPipelineLayoutCreateInfo,
	VkPipelineLayout,
	::vk::PipelineLayoutCreateInfo::structureType,
	::vkCreatePipelineLayout,
	::vkDestroyPipelineLayout
);