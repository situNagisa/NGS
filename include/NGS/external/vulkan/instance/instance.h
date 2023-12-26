#pragma once

#include "./defined.h"

NGS_EXTERNAL_VULKAN_INFO_ENVIRONMENT(InstanceCreateInfo);
NGS_LIB_BEGIN
namespace instance
{
	constexpr auto layers(::std::span<const char* const> param)
	{
		return [=](VkInstanceCreateInfo& info) -> VkInstanceCreateInfo&
			{
				info.enabledLayerCount = static_cast<uint32_t>(param.size());
				info.ppEnabledLayerNames = param.data();
				return info;
			};
	};
	constexpr auto extensions(::std::span<const char* const> param)
	{
		return [=](VkInstanceCreateInfo& info) -> VkInstanceCreateInfo&
			{
				info.enabledExtensionCount = static_cast<uint32_t>(param.size());
				info.ppEnabledExtensionNames = param.data();
				return info;
			};
	};

	constexpr auto app(const VkApplicationInfo& param)
	{
		return [&](VkInstanceCreateInfo& info) -> VkInstanceCreateInfo&
			{
				info.pApplicationInfo = &param;
				return info;
			};
	};
}

NGS_LIB_END