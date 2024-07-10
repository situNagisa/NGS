#pragma once

#include "./defined.h"

NGS_LIB_MODULE_BEGIN

enum class NGS_DLL_API cursor_shape : gl_enum_t {
	arrow = GLFW_ARROW_CURSOR,
	ibeam = GLFW_IBEAM_CURSOR,
	cross_hair = GLFW_CROSSHAIR_CURSOR,
	hand = GLFW_HAND_CURSOR,
	horizontal_resize = GLFW_HRESIZE_CURSOR,
	vertical_resize = GLFW_VRESIZE_CURSOR,
};

NGS_LIB_MODULE_END