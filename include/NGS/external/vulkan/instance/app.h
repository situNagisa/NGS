#pragma once

#include "./defined.h"

NGS_EXTERNAL_VULKAN_INFO_ENVIRONMENT(ApplicationInfo);
NGS_LIB_BEGIN

namespace app
{
	constexpr auto application(::std::string_view name, uint32_t version)
	{
		return [=](VkApplicationInfo& info) -> VkApplicationInfo&
			{
				info.pApplicationName = name.data();
				info.applicationVersion = version;
				return info;
			};
	};

	constexpr auto engine(::std::string_view name, uint32_t version)
	{
		return [=](VkApplicationInfo& info) -> VkApplicationInfo&
			{
				info.pEngineName = name.data();
				info.engineVersion = version;
				return info;
			};
	};
	constexpr auto api(uint32_t version)
	{
		return [=](VkApplicationInfo& info) -> VkApplicationInfo&
			{
				info.apiVersion = version;
				return info;
			};
	};
}

NGS_LIB_END