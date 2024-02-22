#pragma once

#include "./module.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

struct info
{
	NGS_MPL_ENVIRON_BEGIN(info);
public:
	using vulkan_type = trait::info_type;

	vulkan_struct structure{ trait::structure_type };
	VkRenderPass render_pass{ VK_NULL_HANDLE };
	vulkan_range<VkImageView> attachments{};
	uint32_t width = 0;
	uint32_t height = 0;
	uint32_t layers = 1;

	static trait::entity_type create(const self_type& info, const VkDevice& device)
	{
		VkFramebufferCreateInfo create_info{ VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO };
		create_info.renderPass = info.render_pass;
		create_info.attachmentCount = info.attachments.size();
		create_info.pAttachments = info.attachments.data();
		create_info.width = info.width;
		create_info.height = info.height;
		create_info.layers = info.layers;

		trait::entity_type framebuffer{ VK_NULL_HANDLE };
		auto success = trait::create_functor(device, &create_info, nullptr, &framebuffer);
		NGS_ASSERT(success == VK_SUCCESS, "failed to create framebuffer!");
		return framebuffer;
	}

	static void destroy(const VkDevice& device, const trait::entity_type& framebuffer)
	{
		trait::destroy_functor(device, framebuffer, nullptr);
	}

	self_type& set_render_pass(const VkRenderPass& render_pass)
	{
		this->render_pass = render_pass;
		return *this;
	}
	self_type& set_attachments(const vulkan_range<VkImageView>& attachments)
	{
		this->attachments = attachments;
		return *this;
	}
	self_type& set_size(const uint32_t& width, const uint32_t& height)
	{
		this->width = width;
		this->height = height;
		return *this;
	}
	self_type& set_layers(const uint32_t& layers)
	{
		this->layers = layers;
		return *this;
	}
	trait::entity_type create(const VkDevice& device) const
	{
		return self_type::create(*this, device);
	}
};

NGS_LIB_MODULE_END