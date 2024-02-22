#pragma once

#include "./info.h"
#include "./module.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

struct entity : basic_entity<trait>
{
	NGS_MPL_ENVIRON(entity);
public:

	entity(const info& info, const VkDevice& device)
		: base_type(info::create(info, device))
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
