#pragma once

#include "./queue_family.h"
#include "./logical_device.h"
#include "./defined.h"

NGS_LIB_BEGIN

struct physical_device
{
	NGS_MPL_ENVIRON_BEGIN(physical_device);
public:

public:
	physical_device(const self_type& other);
	self_type& operator=(const self_type& other);
	physical_device(self_type&& other) noexcept;
	self_type& operator=(self_type&& other) noexcept;
	physical_device(const ::vk::PhysicalDevice& device);


	auto&& get_device() { return _device; }
	auto&& get_device()const { return _device; }

	auto&& get_queue_families()const { return _queue_families; }

	logical_device create_device();
private:
	void _update_queue_families();
private:
	::vk::PhysicalDevice _device{};
	::std::vector<queue_family> _queue_families{};
};

NGS_LIB_END