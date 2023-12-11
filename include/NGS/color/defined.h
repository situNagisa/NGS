#pragma once

#include "NGS/basic/basic.h"
#include "NGS/cpt/cpt.h"
#include "NGS/bit/bit.h"
#include "NGS/type_trait/type_trait.h"

#define NGS_LIB_VERSION_MAJOR 0
#define NGS_LIB_VERSION_MINOR 2
#define NGS_LIB_VERSION_PATCH 1
#define NGS_LIB_NAME colors
#include "NGS/lib/lib.h"

#undef RGB
#undef _A
#undef _R
#undef _G
#undef _B
#undef __A
#undef __R
#undef __G
#undef __B
#undef _P

NGS_LIB_BEGIN

//enum class color_format : uint32 {
//	unknown,
//
//	argb8,
//	argb15,
//	argb16,
//	argb24,
//	argb32,
//
//	mjpeg,
//
//	yuyv,
//};

struct color_format_d
{
	size_t size;
};

NGS_LIB_END
