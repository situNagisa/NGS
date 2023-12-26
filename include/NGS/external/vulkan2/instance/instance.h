#pragma once

#include "./defined.h"
#include "./info.h"

NGS_LIB_MODULE_BEGIN

struct vulkan : bases::singleton<vulkan>
{
	NGS_MPL_ENVIRON(vulkan);
private:
	friend class base_type;
	constexpr vulkan() = default;
public:
	void initialize(const instance_create_info& info);
	void destroy();

	auto&& get_instance() const noexcept { return _instance; }
	auto&& get_physical_devices() const noexcept { return _physical_devices; }
private:
	::vk::Instance _instance{};
	::std::vector<physical_device> _physical_devices{};
};

NGS_LIB_MODULE_END