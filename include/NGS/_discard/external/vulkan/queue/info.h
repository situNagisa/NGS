#pragma once

#include "./defined.h"
#include "./family.h"

NGS_EXTERNAL_VULKAN_INFO_ENVIRONMENT(DeviceQueueCreateInfo);
NGS_LIB_BEGIN
namespace queues
{
	constexpr auto family(size_t index)
	{
		return [=](VkDeviceQueueCreateInfo& info) -> VkDeviceQueueCreateInfo&
			{
				info.queueFamilyIndex = static_cast<uint32_t>(index);
				return info;
			};
	};
	constexpr auto family(const queue_family& queue_family_)
	{
		return family(queue_family_.get_index());
	};
	constexpr auto priority(const float& priority)
	{
		return [=](VkDeviceQueueCreateInfo& info) -> VkDeviceQueueCreateInfo&
			{
				info.queueCount = 1;
				info.pQueuePriorities = &priority;
				return info;
			};
	};
	constexpr auto priorities(::std::span<const float> priorities)
	{
		return [=](VkDeviceQueueCreateInfo& info) -> VkDeviceQueueCreateInfo&
			{
				info.queueCount = static_cast<uint32_t>(priorities.size());
				info.pQueuePriorities = priorities.data();
				return info;
			};
	};
	constexpr auto priorities(::std::initializer_list<float> priorities)
	{
		return [=](VkDeviceQueueCreateInfo& info) -> VkDeviceQueueCreateInfo&
			{
				info.queueCount = static_cast<uint32_t>(priorities.size());
				info.pQueuePriorities = priorities.begin();
				return info;
			};
	};
}

NGS_LIB_END