#pragma once

#include "./defined.h"
#include "./info.h"

NGS_LIB_MODULE_BEGIN

struct instance : bases::singleton<instance>
{
	NGS_MPL_ENVIRON(instance);
private:
	friend class base_type;
	constexpr instance() = default;
public:
	void initialize(const instance_create_info& info);
	void destroy();

	auto&& get_info() const noexcept { return _info; }
	auto&& get_instance() const noexcept { return _instance; }

private:
	instance_create_info _info;
	vk::Instance _instance{};
};

NGS_LIB_MODULE_END