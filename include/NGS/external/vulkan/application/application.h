#pragma once

#include "./defined.h"

NGS_LIB_BEGIN

struct application : bases::singleton<application>
{
	NGS_MPL_ENVIRON(application);
private:
	friend class base_type;
	constexpr application() = default;
public:
	void initialize(const vk::InstanceCreateInfo& info);

	void destroy();
};

NGS_LIB_END