#pragma once

#include "../basic.h"
#include "./defined.h"

NGS_EXTERNAL_VULKAN_REGISTER_MODULE(
	framebuffer,
	VkFramebufferCreateInfo,
	VkFramebuffer,
	::vk::FramebufferCreateInfo::structureType,
	::vkCreateFramebuffer,
	::vkDestroyFramebuffer
);