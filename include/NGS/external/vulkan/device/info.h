#pragma once

#include "./defined.h"
#include "./physical.h"

NGS_EXTERNAL_VULKAN_INFO_ENVIRONMENT(DeviceCreateInfo);
NGS_LIB_BEGIN
namespace devices
{
	constexpr auto queue(::std::span<VkDeviceQueueCreateInfo> queues)
	{
		return [=](VkDeviceCreateInfo& info) -> VkDeviceCreateInfo&
			{
				info.queueCreateInfoCount = static_cast<uint32_t>(queues.size());
				info.pQueueCreateInfos = queues.data();
				return info;
			};
	};

	constexpr auto layers(::std::span<const char* const> layers)
	{
		return [=](VkDeviceCreateInfo& info) -> VkDeviceCreateInfo&
			{
				info.enabledLayerCount = static_cast<uint32_t>(layers.size());
				info.ppEnabledLayerNames = layers.data();
				return info;
			};
	};

	constexpr auto extensions(::std::span<const char* const> extensions)
	{
		return [=](VkDeviceCreateInfo& info) -> VkDeviceCreateInfo&
			{
				info.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
				info.ppEnabledExtensionNames = extensions.data();
				return info;
			};
	};

	constexpr auto features(const VkPhysicalDeviceFeatures& features = {})
	{
		return [=](VkDeviceCreateInfo& info) -> VkDeviceCreateInfo&
			{
				info.pEnabledFeatures = &features;
				return info;
			};
	};

}

NGS_LIB_END