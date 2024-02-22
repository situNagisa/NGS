#pragma once

#include "../device.h"

#include "./defined.h"

NGS_LIB_BEGIN

struct vulkan : bases::singleton<vulkan>
{
	NGS_MPL_ENVIRON(vulkan);
private:
	friend class base_type;
	constexpr vulkan() = default;
public:
	void initialize(const VkInstanceCreateInfo& info);
	void destroy();

	auto&& get_instance() const noexcept { return _instance; }
	::std::span<physical_device> get_physical_devices() const noexcept { return { _physical_devices ,_physical_devices_count }; }
private:
	::vk::Instance _instance{};
	// vector is not used because of vector need T is copy constructible and copy assignable
	// but physical_device is not copyable
	physical_device* _physical_devices{};
	size_t _physical_devices_count{};
};

NGS_LIB_END