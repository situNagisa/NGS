#pragma once

#include "./defined.h"

NGS_OPENGL_ENUM_BEGIN

enum class NGS_DLL_API cursor_shape : gl_enum_t {
	arrow = GLFW_ARROW_CURSOR,
	ibeam = GLFW_IBEAM_CURSOR,
	crosshair = GLFW_CROSSHAIR_CURSOR,
	hand = GLFW_HAND_CURSOR,
	horizontal_resize = GLFW_HRESIZE_CURSOR,
	vertical_resize = GLFW_VRESIZE_CURSOR,
};

NGS_OPENGL_ENUM_END