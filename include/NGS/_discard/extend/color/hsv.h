#pragma once

#include "NGS/extend/color/defined.h"

NGS_COLOR_SPACE_BEGIN

struct NGS_DLL_API HSV {
	using HueType = byte;
	constexpr static auto HueRate = (bit::mask(bit::as_bit<HueType>())) >= 360 ? 2 : 1;

	constexpr HSV() = default;
	constexpr HSV(byte hue, float32 saturation, float32 value)
		: hue(hue)
		, saturation(saturation)
		, value(value)
	{}

	// 判断HSV颜色是否为红色
	constexpr bool IsRed(float32 tolerance = 0.05f) const {
		return (hue < (7 * HueRate) || hue >(172 * HueRate)) && (saturation > (1 - tolerance)) && (value > (1 - tolerance));
	}

	// 判断HSV颜色是否为绿色
	constexpr bool IsGreen(float32 tolerance = 0.05f) const {
		return (hue > (37 * HueRate)) && (hue < (82 * HueRate)) && (saturation > (1 - tolerance)) && (value > (1 - tolerance));
	}

	// 判断HSV颜色是否为蓝色
	constexpr bool IsBlue(float32 tolerance = 0.05f) const {
		return (hue > (92 * HueRate)) && (hue < (127 * HueRate)) && (saturation > (1 - tolerance)) && (value > (1 - tolerance));
	}

	constexpr HueType Hue()const { return hue; }
	constexpr float32 Saturation()const { return saturation; }
	constexpr float32 Value()const { return value; }

	HueType hue{};
	float32 saturation{};
	float32 value{};
};

NGS_COLOR_SPACE_END
