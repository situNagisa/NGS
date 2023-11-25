#pragma once

#include "./primary.h"
#include "NGS/color/constant.h"

NGS_COLOR_BEGIN
template<CPrimary _T>
struct constant<_T>
{
	using color_type = _T;

	constexpr static color_type red = color_type(standard_ARGB(0xFF, 0xFF, 0x00, 0x00));
	constexpr static color_type green = color_type(standard_ARGB(0xFF, 0x00, 0xFF, 0x00));
	constexpr static color_type blue = color_type(standard_ARGB(0xFF, 0x00, 0x00, 0xFF));
	constexpr static color_type pink = color_type(standard_ARGB(0xFF, 0xFF, 0xC0, 0xCB));
	constexpr static color_type yellow = color_type(standard_ARGB(0xFF, 0xFF, 0xFF, 0x00));
	constexpr static color_type cyan = color_type(standard_ARGB(0xFF, 0x00, 0xFF, 0xFF));
	constexpr static color_type magenta = color_type(standard_ARGB(0xFF, 0xFF, 0x00, 0xFF));
	constexpr static color_type white = color_type(standard_ARGB(0xFF, 0xFF, 0xFF, 0xFF));
	constexpr static color_type black = color_type(standard_ARGB(0xFF, 0x00, 0x00, 0x00));
	constexpr static color_type gray = color_type(standard_ARGB(0xFF, 0x80, 0x80, 0x80));
	constexpr static color_type dark_gray = color_type(standard_ARGB(0xFF, 0x40, 0x40, 0x40));
	constexpr static color_type light_gray = color_type(standard_ARGB(0xFF, 0xC0, 0xC0, 0xC0));
	constexpr static color_type orange = color_type(standard_ARGB(0xFF, 0xFF, 0xA5, 0x00));
	constexpr static color_type brown = color_type(standard_ARGB(0xFF, 0xA5, 0x2A, 0x2A));
	constexpr static color_type purple = color_type(standard_ARGB(0xFF, 0x80, 0x00, 0x80));

};

NGS_COLOR_END