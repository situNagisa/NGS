#pragma once

#include "../basic.h"
#include "./defined.h"

NGS_EXTERNAL_VULKAN_REGISTER_MODULE(
	render_pass,
	VkRenderPassCreateInfo,
	VkRenderPass,
	::vk::RenderPassCreateInfo::structureType,
	::vkCreateRenderPass,
	::vkDestroyRenderPass
);