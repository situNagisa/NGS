#pragma once

#include "NGS/basic/basic.h"
#include "NGS/cpt/cpt.h"
#include "NGS/bit/bit.h"
#include "NGS/type_trait/type_trait.h"

#define NGS_COLOR_BEGIN NGS_BEGIN namespace colors{
#define NGS_COLOR_END } NGS_END

#undef RGB
#undef _A
#undef _R
#undef _G
#undef _B
#undef __A
#undef __R
#undef __G
#undef __B

NGS_COLOR_BEGIN

enum class color_format : uint32 {
	unknown,

	argb8,
	argb15,
	argb16,
	argb24,
	argb32,

	mjpeg,

	yuyv,
};

struct color_format_d
{
	size_t size;
};

NGS_COLOR_END
