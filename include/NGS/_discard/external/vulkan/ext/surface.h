#pragma once

#include "../device.h"
#include "../queue.h"

#include "./defined.h"

NGS_LIB_MODULE_BEGIN

struct surface
{
	NGS_MPL_ENVIRON_BEGIN(surface);
public:
	surface() = default;
	surface(const VkSurfaceKHR& surface, physical_device& physical_device);

	surface(const VkSurfaceKHR& surface);

	decltype(auto) operator()(VkSwapchainCreateInfoKHR& info)const
	{
		info.surface = _surface;
		return info;
	}

	bool is_support(const queue_family& queue_family)const;
	bool is_support()const { return !get_support_queue_families().empty(); }

	void set_physical_device(const physical_device& physical_device) { _physical_device = &physical_device; }

	auto get_support_queue_families()const
	{
		NGS_ASSERT(_physical_device, "physical device is null");
		return ::std::ranges::views::filter(_physical_device->get_queue_families(), [this](const queue_family& family) {return is_support(family); });
	}

	auto&& get_surface() { return _surface; }

	auto&& get_surface()const { return _surface; }
	auto&& get_physical_device()const { return _physical_device; }

	auto get_capabilities()const
	{
		NGS_ASSERT(_physical_device, "physical device is null");
		return _physical_device->get_device().getSurfaceCapabilitiesKHR(_surface);
	}
	auto get_formats()const
	{
		NGS_ASSERT(_physical_device, "physical device is null");
		return _physical_device->get_device().getSurfaceFormatsKHR(_surface);
	}

	auto get_present_modes()const
	{
		NGS_ASSERT(_physical_device, "physical device is null");
		return _physical_device->get_device().getSurfacePresentModesKHR(_surface);
	}
private:
	::vk::SurfaceKHR _surface{};
	const physical_device* _physical_device = nullptr;
};

NGS_LIB_MODULE_END