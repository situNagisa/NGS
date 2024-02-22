#pragma once

#include "./physical.h"
#include "./defined.h"

NGS_LIB_BEGIN
NGS_HPP_INLINE physical_device::physical_device(::vk::PhysicalDevice device)
	: _device(device)
{
	auto propertieses = _device.getQueueFamilyProperties();

	//TODO: 建立memory库，用于管理内存

	_queue_families_count = propertieses.size();
	_queue_families = static_cast<queue_family*>(::std::malloc(sizeof(queue_family) * _queue_families_count));
	for (size_t i = 0; i < _queue_families_count; ++i)
	{
		new(_queue_families + i) queue_family(this, propertieses[i], i);
	}
}

NGS_HPP_INLINE physical_device::~physical_device()
{
	for (auto&& queue_family : get_queue_families())
	{
		queue_family.~queue_family();
	}
	::std::free(_queue_families);
}

NGS_HPP_INLINE logical_device physical_device::create_device(const VkDeviceCreateInfo& info)
{
	return { this, _device.createDevice(info) };
}


NGS_LIB_END
