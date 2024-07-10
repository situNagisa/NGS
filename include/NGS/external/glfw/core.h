#pragma once

#include "./detail.h"

NGS_LIB_BEGIN

using details::graphic_api;
using details::glfw_guard;
namespace guards
{
	using details::opengl_guard;
	using details::vulkan_guard;
}

using details::window;

NGS_LIB_END