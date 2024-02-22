#pragma once

#include "../queue.h"
#include "./logical.h"
#include "./defined.h"

NGS_LIB_BEGIN

struct physical_device : bases::delete_copy
{
	NGS_MPL_ENVIRON_BEGIN(queue_family);
private:
	friend struct vulkan;
	physical_device(::vk::PhysicalDevice device);
	~physical_device();
public:

	auto&& get_device() { return _device; }
	auto&& get_device()const { return _device; }

	::std::span<queue_family> get_queue_families()const { return { _queue_families,_queue_families_count }; }

	logical_device create_device(const VkDeviceCreateInfo& info);
private:
	::vk::PhysicalDevice _device;
	queue_family* _queue_families;
	size_t _queue_families_count;
};

NGS_LIB_END