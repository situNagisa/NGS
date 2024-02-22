#pragma once

#include "./instance.h"

NGS_LIB_MODULE_BEGIN

NGS_HPP_INLINE void vulkan::initialize(const instance_create_info& info)
{
	_instance = vk::createInstance(info.create_instance_info(info.create_application_info()));

	for (auto&& device : _instance.enumeratePhysicalDevices())
		_physical_devices.emplace_back(device);
}

NGS_HPP_INLINE void vulkan::destroy()
{
	_instance.destroy();
}

NGS_LIB_MODULE_END
