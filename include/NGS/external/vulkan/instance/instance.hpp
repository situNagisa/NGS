#pragma once

#include"./instance.h"

NGS_LIB_MODULE_BEGIN

NGS_HPP_INLINE void instance::initialize(const instance_create_info& info)
{
	_info = info;

	vk::ApplicationInfo app_info{};
	app_info.pApplicationName = _info.application.name.data();
	app_info.applicationVersion = _info.application.version;
	app_info.pEngineName = _info.engine.name.data();
	app_info.engineVersion = _info.engine.version;
	app_info.apiVersion = _info.version;

	vk::InstanceCreateInfo create_info{};
	create_info.pApplicationInfo = &app_info;
	{
		::std::vector<const char*> extensions(_info.extensions.size());
		::std::ranges::transform(_info.extensions, extensions.begin(), [](::std::string_view str) { return str.data(); });

		create_info.enabledExtensionCount = static_cast<uint32_t>(extensions.size());
		create_info.ppEnabledExtensionNames = extensions.data();
	}
	{
		::std::vector<const char*> layers(_info.layers.size());
		::std::ranges::transform(_info.layers, layers.begin(), [](::std::string_view str) { return str.data(); });

		create_info.enabledLayerCount = static_cast<uint32_t>(layers.size());
		create_info.ppEnabledLayerNames = layers.data();
	}

	_instance = vk::createInstance(create_info);
}

NGS_HPP_INLINE void instance::destroy()
{
	_instance.destroy();
	_info = {};
}

NGS_LIB_MODULE_END
