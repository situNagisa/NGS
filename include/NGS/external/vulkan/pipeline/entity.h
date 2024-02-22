#pragma once

#include "./info.h"

NGS_LIB_MODULE_BEGIN

struct entity : basic_entity<trait>
{
	NGS_MPL_ENVIRON(entity);
public:

public:

	entity(const info& info, const VkDevice& device, const VkPipelineLayout& layout, const VkRenderPass& render_pass, const VkPipeline& pipeline)
		: base_type(info::create(info, device, layout, render_pass, pipeline))
		, _device(device)
	{}
	~entity()
	{
		info::destroy(_device, value());
	}
private:
	const VkDevice& _device;
};

NGS_LIB_MODULE_END