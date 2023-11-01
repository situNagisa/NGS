#pragma once

#include "NGS/basic/basic.h"
#include "NGS/cpt/cpt.h"
#include "NGS/bit/bit.h"
#include "NGS/type_trait/type_trait.h"

#define NGS_COLOR_BEGIN NGS_BEGIN namespace colors{
#define NGS_COLOR_END } NGS_END

#undef RGB

NGS_COLOR_BEGIN

enum class color_format : uint32 {
	unknown,

	ARGB8,
	ARGB15,
	ARGB16,
	ARGB24,
	ARGB32,

	MJPEG,

	YUYV,
};

struct color_format_d
{
	size_t size;
};

NGS_COLOR_END
