#pragma once

#include "./defined.h"

NGS_LIB_BEGIN

struct queue_family : bases::delete_copy
{
	NGS_MPL_ENVIRON_BEGIN(queue_family);
private:
	friend struct physical_device;
	queue_family(const physical_device* device, const ::vk::QueueFamilyProperties& properties, size_t index)
		: _device(device)
		, _properties(properties)
		, _index(index)
	{}
public:
	auto&& get_device()const { return _device; }
	auto&& get_properties()const { return _properties; }
	auto&& get_index()const { return _index; }
private:
	const physical_device* _device;
	::vk::QueueFamilyProperties _properties;
	size_t _index = 0;
};

NGS_LIB_END