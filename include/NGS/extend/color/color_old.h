#pragma  once

#include "NGS/base/base.h"



NGS_BEGIN


NGS_TYPE





#undef max
#undef min

template<typename _From, typename _To>
_To Convert(const _From& from);

template<>
constexpr HSV Convert<ARGB24, HSV>(const ARGB24& argb) {
	byte hue;
	float32
		saturation,
		value
		;

	float32 r = (float32)ARGB24::R::Percent(argb.Red());
	float32 g = (float32)ARGB24::G::Percent(argb.Green());
	float32 b = (float32)ARGB24::B::Percent(argb.Blue());

	float32 max = std::max(r, std::max(g, b));
	float32 min = std::min(r, std::min(g, b));
	float32 delta = max - min;

	value = max;

	if (max)
		saturation = delta / max;
	else {
		saturation = 0;
		hue = 0;
		return HSV(hue, saturation, value);
	}

	if (r == max)
		hue = byte((g - b) / delta);
	else if (g == max)
		hue = byte(2 + (b - r) / delta);
	else
		hue = byte(4 + (r - g) / delta);

	hue *= 30 * HSV::HueRate;
	if (hue < 0)
		hue += 180 * HSV::HueRate;
	return HSV(hue, saturation, value);
}

template<>
constexpr ARGB24 Convert <HSV, ARGB24>(const HSV& hsv) {
	float32
		h = hsv.Hue(),
		s = hsv.Saturation(),
		v = hsv.Value()
		;
	float32 r, g, b;
	if (s == 0) {
		r = g = b = v;
	}
	else {
		h /= 30 * HSV::HueRate;
		int32 i = (int32)h;
		float32 f = h - i;
		float32 p = v * (1 - s);
		float32 q = v * (1 - s * f);
		float32 t = v * (1 - s * (1 - f));
		switch (i) {
		case 0: r = v; g = t; b = p; break;
		case 1: r = q; g = v; b = p; break;
		case 2: r = p; g = v; b = t; break;
		case 3: r = p; g = q; b = v; break;
		case 4: r = t; g = p; b = v; break;
		case 5: r = v; g = p; b = q; break;
		default: r = g = b = 0; break;
		}
	}
	return ARGB24(
		0,
		ARGB24::R::ConvertFrom<StdChannel>(byte(r * ARGB24::R::Filter)),
		ARGB24::G::ConvertFrom<StdChannel>(byte(g * ARGB24::R::Filter)),
		ARGB24::B::ConvertFrom<StdChannel>(byte(b * ARGB24::R::Filter))
	);
}

NGS_END

class NGS_API  Color {
public:
	NGS_TYPE_DEFINE(uint8, channel);

	struct NGS_API Blend {
	public:
		template<_NGS_CPT CARGB rgb = _NGS_TYP StdARGB>
		constexpr static typename rgb::A::type RGB_AlphaBlend(rgb::A::type alphaA, rgb::A::type alphaB) {
			uint16 a = alphaA + 1;
			uint16 b = alphaB + 1;
			return a + b - ((a * b) >> rgb::A::count) - 1;
		}
		template<_NGS_CPT CARGB rgb = _NGS_TYP StdARGB>
		constexpr static __channel RGB_AlphaBlend(__channel fore, __channel back, __channel alphaF, __channel alphaB) {
			constexpr auto alpha_bitcount = rgb::A::count;
			constexpr auto alpha_bitmax = rgb::A::filter;
			auto alpha_blend = RGB_AlphaBlend<rgb>(alphaF, alphaB);

			return ((fore * alphaF + (back * alphaB * (alpha_bitmax - alphaF) >> alpha_bitcount)) * alpha_blend) >> (alpha_bitcount << 1);
		}

		template<_NGS_CPT CARGB rgb = _NGS_TYP StdARGB>
		constexpr static typename rgb::type RGB_AlphaBlend(rgb::type fore, rgb::type back) {
			rgb result{ 0 };
			rgb foreground = fore;
			rgb background = back;
			result.Alpha(RGB_AlphaBlend<rgb>(foreground.Alpha(), background.Alpha()));
			result.Red(RGB_AlphaBlend<rgb>(foreground.Red(), background.Red(), foreground.Alpha(), background.Alpha()));
			result.Green(RGB_AlphaBlend<rgb>(foreground.Green(), background.Green(), foreground.Alpha(), background.Alpha()));
			result.Blue(RGB_AlphaBlend<rgb>(foreground.Blue(), background.Blue(), foreground.Alpha(), background.Alpha()));
			return result;
		}
	};
};

namespace color_constants {
	template<class  _Color>
	constexpr auto white = _Color(StdARGB(0xFF, 0xFF, 0xFF, 0xFF));//白色
	template<class  _Color>
	constexpr auto black = _Color(StdARGB(0xFF, 0x00, 0x00, 0x00));//黑色
	template<class  _Color>
	constexpr auto red = _Color(StdARGB(0xFF, 0xFF, 0x00, 0x00));//红色
	template<class  _Color>
	constexpr auto green = _Color(StdARGB(0xFF, 0x00, 0xFF, 0x00));//绿色
	template<class  _Color>
	constexpr auto blue = _Color(StdARGB(0xFF, 0x00, 0x00, 0xFF));//蓝色
	template<class  _Color>
	constexpr auto cyan = _Color(StdARGB(0xFF, 0x00, 0xFF, 0xFF));//青色
	template<class  _Color>
	constexpr auto purple = _Color(StdARGB(0xFF, 0xFF, 0x00, 0xFF));//紫色
	template<class  _Color>
	constexpr auto yellow = _Color(StdARGB(0xFF, 0xFF, 0xFF, 0x00));//黄色
	template<class  _Color>
	constexpr auto gray = _Color(StdARGB(0xFF, 0x80, 0x80, 0x80));//灰色
	template<class  _Color>
	constexpr auto lightgray = _Color(StdARGB(0xFF, 0xC0, 0xC0, 0xC0));//浅灰色
	template<class  _Color>
	constexpr auto darkgray = _Color(StdARGB(0xFF, 0x40, 0x40, 0x40));//深灰色
	template<class  _Color>
	constexpr auto transparent = _Color(StdARGB(0x00, 0x00, 0x00, 0x00));//透明色
}

using ColorConvert = mpl::bitmap<PixelFormat,
	mpl::bitmap_item<ARGB8, (uint32)PixelFormat::ARGB8 >,
	mpl::bitmap_item<ARGB15, (uint32)PixelFormat::ARGB15>,
	mpl::bitmap_item<ARGB16, (uint32)PixelFormat::ARGB16>,
	mpl::bitmap_item<ARGB24, (uint32)PixelFormat::ARGB24>,
	mpl::bitmap_item<ARGB32, (uint32)PixelFormat::ARGB32>
>;



NGS_END