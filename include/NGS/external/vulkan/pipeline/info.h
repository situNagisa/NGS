#pragma once

#include "../info.h"
#include "./defined.h"

NGS_EXTERNAL_VULKAN_INFO_ENVIRONMENT(GraphicsPipelineCreateInfo);
NGS_LIB_BEGIN
namespace pipelines
{
	constexpr auto stage(::std::span<const VkPipelineShaderStageCreateInfo> shaders)
	{
		return [=](VkGraphicsPipelineCreateInfo& info) -> VkGraphicsPipelineCreateInfo&
			{
				info.stageCount = static_cast<uint32_t>(shaders.size());
				info.pStages = shaders.data();
				return info;
			};
	};
	constexpr auto stage(::std::initializer_list<const VkPipelineShaderStageCreateInfo> shaders) { return stage(::std::span(shaders)); }
	constexpr auto stage(const VkPipelineShaderStageCreateInfo& shader) { return stage(::std::span(&shader, 1)); }


}
NGS_LIB_END