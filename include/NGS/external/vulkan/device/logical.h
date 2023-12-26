#pragma once

#include "./defined.h"

NGS_LIB_BEGIN

struct logical_device
{
	NGS_MPL_ENVIRON_BEGIN(logical_device);
private:
	friend struct physical_device;
	logical_device(physical_device* physical_device, const ::vk::Device& logical_device)
		: _physical_device(physical_device)
		, _device(logical_device)
	{}
public:

	auto&& get_physical_device()const { return _physical_device; }
	auto&& get_device()const { return _device; }

private:
	physical_device* _physical_device;
	::vk::Device _device;
};

NGS_LIB_END