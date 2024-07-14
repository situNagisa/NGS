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

namespace hints = details::hints;
using details::window_hint;
using details::hint_t;
using details::hint_v;

NGS_LIB_END