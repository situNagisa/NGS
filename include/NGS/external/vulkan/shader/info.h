#pragma once

#include "../basic.h"
#include "./module.h"
#include "./defined.h"


NGS_LIB_BEGIN
namespace enums
{

}
NGS_LIB_END
NGS_LIB_MODULE_BEGIN

struct info
{
	NGS_MPL_ENVIRON_BEGIN(info);
public:
	using vulkan_type = trait::info_type;

	vulkan_struct structure{ trait::structure_type };
	::std::span<const byte> code{};

	auto to_vulkan()const
	{
		return vulkan_type
		{
			.sType = static_cast<VkStructureType>(structure.type),
			.pNext = structure.next,
			.flags = structure.flags,
			.codeSize = code.size(),
			.pCode = reinterpret_cast<const uint32_t*>(code.data()),
		};
	}

	static auto create(const self_type& self, const VkDevice& device)
	{
		trait::entity_type result{};

		auto&& vulkan_info = NGS_LIB_NAME::to_vulkan(self);

		trait::create_functor(device, &vulkan_info, nullptr, &result);

		return result;
	}
	static void destroy(const VkDevice& device, const trait::entity_type& entity)
	{
		trait::destroy_functor(device, entity, nullptr);
	}
};
static_assert(vulkan_info<info>);

NGS_LIB_MODULE_END