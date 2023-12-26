#pragma once

#include "./surface.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

NGS_HPP_INLINE surface::surface(const VkSurfaceKHR& surface, physical_device& physical_device)
	: _surface(surface)
	, _physical_device(&physical_device)
{}

NGS_HPP_INLINE surface::surface(const VkSurfaceKHR& surface)
	: _surface(surface)
	, _physical_device(nullptr)
{}

NGS_HPP_INLINE bool surface::is_support(const queue_family& queue_family) const
{
	return queue_family.get_device()->get_device().getSurfaceSupportKHR(static_cast<uint32_t>(queue_family.get_index()), _surface);
}

NGS_LIB_MODULE_END
