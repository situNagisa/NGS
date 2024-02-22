#pragma once

#include "../basic.h"
#include "./defined.h"

NGS_EXTERNAL_VULKAN_REGISTER_MODULE(
	graphic_pipeline,
	VkGraphicsPipelineCreateInfo,
	VkPipeline,
	::vk::GraphicsPipelineCreateInfo::structureType,
	::vkCreateGraphicsPipelines,
	::vkDestroyPipeline
);