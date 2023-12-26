#pragma once

#include "./vulkan.h"
#include "./defined.h"

NGS_LIB_BEGIN

NGS_HPP_INLINE void vulkan::initialize(const VkInstanceCreateInfo& info)
{
	_instance = ::vk::createInstance(info);

	//construct physical devices
	{
		auto physical_devices = _instance.enumeratePhysicalDevices();

		_physical_devices_count = physical_devices.size();
		_physical_devices = static_cast<physical_device*>(::std::malloc(sizeof(physical_device) * _physical_devices_count));
		for (size_t i = 0; i < _physical_devices_count; ++i)
		{
			new(_physical_devices + i) physical_device(physical_devices[i]);
		}
	}
}

NGS_HPP_INLINE void vulkan::destroy()
{
	for (auto&& physical_device : get_physical_devices())
	{
		physical_device.~physical_device();
	}
	::std::free(_physical_devices);
}

NGS_LIB_END
