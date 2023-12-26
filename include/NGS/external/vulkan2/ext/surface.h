#pragma once

#include "./defined.h"

NGS_LIB_MODULE_BEGIN

struct surface
{
	NGS_MPL_ENVIRON_BEGIN(surface);
public:
	constexpr surface() = default;
	constexpr surface(const ::vk::SurfaceKHR& surface, physical_device& physical_device)
		: _surface(surface)
		, _physical_device(&physical_device)
	{}
	constexpr surface(const ::vk::SurfaceKHR& surface)
		: _surface(surface)
		, _physical_device(nullptr)
	{}

	bool is_support(const queue_family& queue_family)const
	{
		return queue_family.get_device()->get_device().getSurfaceSupportKHR(static_cast<uint32_t>(queue_family.get_index()), _surface);
	}
	bool is_support()const
	{
		return !get_support_queue_families().empty();
	}

	void set_physical_device(const physical_device& physical_device) { _physical_device = &physical_device; }

	[[nodiscard]] auto get_support_queue_families()const
	{
		NGS_ASSERT(_physical_device, "physical device is null");
		return ::std::ranges::views::filter(_physical_device->get_queue_families(), [this](const queue_family& family) {return is_support(family); });
	}

	[[nodiscard]] auto&& get_surface() { return _surface; }

	[[nodiscard]] auto&& get_surface()const { return _surface; }
	[[nodiscard]] auto&& get_physical_device()const { return _physical_device; }

	[[nodiscard]] auto get_capabilities()const
	{
		NGS_ASSERT(_physical_device, "physical device is null");
		return _physical_device->get_device().getSurfaceCapabilitiesKHR(_surface);
	}
	[[nodiscard]] auto get_formats()const
	{
		NGS_ASSERT(_physical_device, "physical device is null");
		return _physical_device->get_device().getSurfaceFormatsKHR(_surface);
	}

	[[nodiscard]] auto get_present_modes()const
	{
		NGS_ASSERT(_physical_device, "physical device is null");
		return _physical_device->get_device().getSurfacePresentModesKHR(_surface);
	}
private:
	::vk::SurfaceKHR _surface{};
	const physical_device* _physical_device = nullptr;
};

NGS_LIB_MODULE_END