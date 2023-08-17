#pragma once

#include "NGS/base/base.h"

#define NGS_COLOR_SPACE_BEGIN NGS_BEGIN inline namespace color_space{
#define NGS_COLOR_SPACE_END } NGS_END

#undef RGB

NGS_COLOR_SPACE_BEGIN

enum class  PixelType : uint32 {
	unknown,

	ARGB8,
	ARGB15,
	ARGB16,
	ARGB24,
	ARGB32,

	MJPEG,

	YUYV,
};

struct NGS_API PixelFormat {
	size_t size;
};

NGS_COLOR_SPACE_END
