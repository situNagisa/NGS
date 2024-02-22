#pragma once

#include "../pipeline.h"
#include "./module.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

struct info
{
	NGS_MPL_ENVIRON_BEGIN(info);
public:
	using vulkan_type = trait::info_type;

	struct push_constant_range_type
	{
		using vulkan_type = VkPushConstantRange;

		enums::shader_stage_flag stage{};
		math::boxes::containers::hypercube<1, uint32_t, uint32_t> range{};

		vulkan_type to_vulkan()const
		{
			return {
				.stageFlags = static_cast<VkShaderStageFlags>(stage),
				.offset = range.position()[0],
				.size = range.size()[0],
			};
		}
	};

	vulkan_struct structure{ trait::structure_type };
	//
	vulkan_range<push_constant_range_type> push_constant_ranges{};

	static trait::entity_type create(const self_type& info, const VkDevice& device)
	{
		auto push_ranges = NGS_LIB_NAME::to_vulkan_vector(info.push_constant_ranges);

		VkPipelineLayoutCreateInfo create_info{};
		create_info.sType = static_cast<VkStructureType>(info.structure.type);
		create_info.setLayoutCount = 0;
		create_info.pSetLayouts = nullptr;
		create_info.pushConstantRangeCount = static_cast<uint32_t>(push_ranges.size());
		create_info.pPushConstantRanges = push_ranges.data();

		trait::entity_type result{};
		::vkCreatePipelineLayout(device, &create_info, nullptr, &result);
		return result;
	}

	static void destroy(const VkDevice& device, const trait::entity_type& entity)
	{
		::vkDestroyPipelineLayout(device, entity, nullptr);
	}
};

NGS_LIB_MODULE_END