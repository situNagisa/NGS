#pragma once

#include "./defined.h"

NGS_LIB_MODULE_BEGIN

struct instance_create_info
{
	vk::InstanceCreateFlags flags{};
	struct
	{
		std::string name{};
		uint32_t version{};
		void_ptr_cst next = nullptr;
	}application{};
	struct
	{
		std::string name{};
		uint32_t version{};
	}engine{};
	uint32_t version{};

	::std::span<const char* const> layers{};
	::std::span<const char* const> extensions{};

	void_ptr_cst next = nullptr;

	constexpr auto create_application_info()const noexcept
	{
		::vk::ApplicationInfo result{};
		result.pApplicationName = application.name.data();
		result.applicationVersion = application.version;
		result.pEngineName = engine.name.data();
		result.engineVersion = engine.version;
		result.apiVersion = version;
		result.pNext = application.next;

		return result;
	}

	constexpr auto create_instance_info(const ::vk::ApplicationInfo& app_info)const noexcept
	{
		::vk::InstanceCreateInfo result{};
		result.pApplicationInfo = &app_info;
		result.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
		result.ppEnabledExtensionNames = extensions.data();
		result.enabledLayerCount = static_cast<uint32_t>(layers.size());
		result.ppEnabledLayerNames = layers.data();
		result.pNext = next;

		return result;
	}
};

NGS_LIB_MODULE_END

NGS_LIB_MODULE_EXPORT(instance_create_info);