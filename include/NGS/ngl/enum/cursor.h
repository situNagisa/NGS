#pragma once

#include "NGS/ngl/defined.h"

NGL_BEGIN

enum class CursorShape : int {
	arrow = GLFW_ARROW_CURSOR,
	ibeam = GLFW_IBEAM_CURSOR,
	crosshair = GLFW_CROSSHAIR_CURSOR,
	hand = GLFW_HAND_CURSOR,
	hresize = GLFW_HRESIZE_CURSOR,
	vresize = GLFW_VRESIZE_CURSOR,
};

NGL_END