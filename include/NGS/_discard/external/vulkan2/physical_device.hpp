#pragma once

#include "./physical_device.h"

NGS_LIB_BEGIN

NGS_HPP_INLINE physical_device::physical_device(const self_type& other)
	: _device(other._device)
	, _queue_families(other._queue_families)
{
	_update_queue_families();
}

NGS_HPP_INLINE physical_device::self_type& physical_device::operator=(const self_type& other)
{
	_device = other._device;
	_queue_families = other._queue_families;
	_update_queue_families();
}

NGS_HPP_INLINE physical_device::physical_device(self_type&& other) noexcept
	: _device(::std::move(other._device))
	, _queue_families(::std::move(other._queue_families))
{
	_update_queue_families();
}

NGS_HPP_INLINE physical_device::self_type& physical_device::operator=(self_type&& other) noexcept
{
	_device = ::std::move(other._device);
	_queue_families = ::std::move(other._queue_families);
	_update_queue_families();
}

NGS_HPP_INLINE physical_device::physical_device(const vk::PhysicalDevice& device)
	: _device(device)
{
	auto propertieses = _device.getQueueFamilyProperties();
	_queue_families.reserve(propertieses.size());
	for (auto i = propertieses.begin(); i != propertieses.end(); ++i)
	{
		_queue_families.push_back(queue_family(this, *i, i - propertieses.begin()));
	}
}

NGS_HPP_INLINE void physical_device::_update_queue_families()
{
	for (auto&& queue_family : _queue_families)
	{
		queue_family._device = this;
	}
}


NGS_LIB_END
