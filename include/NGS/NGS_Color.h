#pragma  once

#include "NGS/NGS_Defined.h"
#include "NGS/NGS_STL.h"
#include "NGS/NGS_Bit.h"
#include "NGS/NGS_Concepts.h"
#include "NGS/NGS_TypeTrait.h"

#undef RGB

NGS_BEGIN

NGS_CONCEPT

template<typename T>
concept Channel_C = requires(T t) {
	{ T::Count } -> std::convertible_to<size_t>;
	{ T::Offset } -> std::convertible_to<size_t>;
	{ T::Filter } -> std::convertible_to<size_t>;
	{ T::FilterWithOffset } -> std::convertible_to<size_t>;
	std::is_integral_v<typename T::type>;
};
NGS_END

NGS_TYPE
template<size_t _Count, size_t _Offset>
struct Channel {
	static constexpr size_t Count = _Count;
	static constexpr size_t Offset = _Offset;

	using type = byte_<ByteOf(Count)>;

	static constexpr type Filter = bit_max(Count);
	static constexpr  size_t FilterWithOffset = Filter << Offset;

	static constexpr float64 Percent(type value) {
		return static_cast<float64>(value) / Filter;
	}

	template<_CPT Channel_C _Channel>
	static constexpr _Channel::type ConvertTo(type value) {
		//这里很关键！一定要检测非0，不然常量表达式不通过
		if constexpr (Filter)
			//这里也很关键！顺序不能改！常量表达式中不允许浮点数转换为整数，所以必须先乘再除
			return (size_t)value * _Channel::Filter / Filter;
		else
			return 0;
	}
	template<size_t _Count2, size_t _Offset2>
	static constexpr Channel<_Count2, _Offset2>::type ConvertTo(type value) {
		return ConvertTo < Channel<_Count2, _Offset2>>(value);
	}
	template<_CPT Channel_C _Channel>
	static constexpr type ConvertFrom(_Channel::type value) {
		//这里很关键！一定要检测非0，不然常量表达式不通过
		if constexpr (_Channel::Filter)
			//这里也很关键！顺序不能改！常量表达式中不允许浮点数转换为整数，所以必须先乘再除
			return value * Filter / _Channel::Filter;
		else
			return 0;
	}
	template<size_t _Count2, size_t _Offset2>
	static constexpr type ConvertFrom(Channel<_Count2, _Offset2>::type value) {
		return ConvertFrom< Channel<_Count2, _Offset2>>(value);
	}
private:
	Channel() = default;
};
using StdChannel = Channel<8, 0>;

static_assert(_CPT Channel_C<StdChannel>);
NGS_END

NGS_CONCEPT
template<typename T>
concept ARGB_C = requires(T t) {
	Channel_C<typename T::A>;
	Channel_C<typename T::R>;
	Channel_C<typename T::G>;
	Channel_C<typename T::B>;
	std::integral<typename T::type>;

	{ t.Alpha() } -> std::convertible_to<typename T::A::type>;
	{ t.Red() } -> std::convertible_to<typename T::R::type>;
	{ t.Green() } -> std::convertible_to<typename T::G::type>;
	{ t.Blue() } -> std::convertible_to<typename T::B::type>;
	{ t.StdAlpha() } -> std::convertible_to<StdChannel::type>;
	{ t.StdRed() } -> std::convertible_to<StdChannel::type>;
	{ t.StdGreen() } -> std::convertible_to<StdChannel::type>;
	{ t.StdBlue() } -> std::convertible_to<StdChannel::type>;
};
NGS_END

NGS_TYPE
#undef _A
#undef _R
#undef _G
#undef _B
template<size_t _A, size_t _R, size_t _G, size_t _B>
struct ARGB {
public:
	using A = Channel<_A, _A + _R + _G>;
	using R = Channel<_R, _A + _R>;
	using G = Channel<_G, _A>;
	using B = Channel<_B, 0>;
	using type = byte_<ByteOf(_A + _R + _G + _B)>;

	static constexpr uint32
		Filter = A::FilterWithOffset | R::FilterWithOffset | G::FilterWithOffset | B::FilterWithOffset
		;

	constexpr ARGB() = default;
	constexpr ARGB(type value) : _value(value) {}

	constexpr ARGB(
		StdChannel::type a,
		StdChannel::type r,
		StdChannel::type g,
		StdChannel::type b
	)
		: _value(
			(A::template ConvertFrom<StdChannel>(a) << A::Offset) |
			(R::template ConvertFrom<StdChannel>(r) << R::Offset) |
			(G::template ConvertFrom<StdChannel>(g) << G::Offset) |
			(B::template ConvertFrom<StdChannel>(b) << B::Offset)
		)
	{}

	constexpr A::type Alpha() const { return ((_value >> A::Offset) & A::Filter); }
	void Alpha(A::type a) { _value = ((a << A::Offset) & A::FilterWithOffset) | (_value & ~A::FilterWithOffset); }
	constexpr R::type Red() const { return ((_value >> R::Offset) & R::Filter); }
	void Red(R::type r) { _value = ((r << R::Offset) & R::FilterWithOffset) | (_value & ~R::FilterWithOffset); }
	constexpr G::type Green() const { return ((_value >> G::Offset) & G::Filter); }
	void Green(G::type g) { _value = ((g << G::Offset) & G::FilterWithOffset) | (_value & ~G::FilterWithOffset); }
	constexpr B::type Blue() const { return ((_value >> B::Offset) & B::Filter); }
	void Blue(B::type b) { _value = ((b << B::Offset) & B::FilterWithOffset) | (_value & ~B::FilterWithOffset); }

	constexpr StdChannel::type StdAlpha()const { return A::template ConvertTo<StdChannel>(Alpha()); }
	void StdAlpha(StdChannel::type a) { Alpha(A::template ConvertFrom<StdChannel>(a)); }
	constexpr StdChannel::type StdRed()const { return R::template ConvertTo<StdChannel>(Red()); }
	void StdRed(StdChannel::type r) { Red(R::template ConvertFrom<StdChannel>(r)); }
	constexpr StdChannel::type StdGreen()const { return G::template ConvertTo<StdChannel>(Green()); }
	void StdGreen(StdChannel::type g) { Green(G::template ConvertFrom<StdChannel>(g)); }
	constexpr StdChannel::type StdBlue()const { return B::template ConvertTo<StdChannel>(Blue()); }
	void StdBlue(StdChannel::type b) { Blue(B::template ConvertFrom<StdChannel>(b)); }


	template<size_t _A2, size_t _R2, size_t _G2, size_t _B2>
	operator ARGB<_A2, _R2, _G2, _B2>()const {
		return ARGB<_A2, _R2, _G2, _B2>(
			StdAlpha(),
			StdRed(),
			StdGreen(),
			StdBlue()
		);
	}
private:
	type _value;
};

using ARGB32 = ARGB<8, 8, 8, 8>;
using ARGB24 = ARGB<0, 8, 8, 8>;
using ARGB16 = ARGB<0, 5, 6, 5>;
using ARGB15 = ARGB<1, 5, 5, 5>;
using ARGB8 = ARGB<0, 3, 3, 2>;

using StdARGB = ARGB32;

static_assert(_CPT ARGB_C<StdARGB>);

struct HSV {
	using HueType = byte;
	constexpr static auto HueRate = (bit_max(BitsOf<HueType>())) >= 360 ? 2 : 1;

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

	HueType hue;
	float32 saturation;
	float32 value;
};

template<typename _From, typename _To>
_To Convert(const _From& from);

template<>
constexpr HSV Convert<ARGB24, HSV>(const ARGB24& argb) {
	byte hue;
	float32
		saturation,
		value
		;

	float32 r = ARGB24::R::Percent(argb.Red());
	float32 g = ARGB24::G::Percent(argb.Green());
	float32 b = ARGB24::B::Percent(argb.Blue());

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
		hue = (g - b) / delta;
	else if (g == max)
		hue = 2 + (b - r) / delta;
	else
		hue = 4 + (r - g) / delta;

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
		ARGB24::R::ConvertFrom<StdChannel>(r * ARGB24::R::Filter),
		ARGB24::G::ConvertFrom<StdChannel>(g * ARGB24::R::Filter),
		ARGB24::B::ConvertFrom<StdChannel>(b * ARGB24::R::Filter)
	);
}

NGS_END

class Color {
public:
	NGS_TYPE_DEFINE(uint8, channel);

	struct Blend {
	public:
		template<_CPT ARGB_C rgb = _TYP StdARGB>
		constexpr static typename rgb::A::type RGB_AlphaBlend(rgb::A::type alphaA, rgb::A::type alphaB) {
			uint16 a = alphaA + 1;
			uint16 b = alphaB + 1;
			return a + b - ((a * b) >> rgb::A::count) - 1;
		}
		template<_CPT ARGB_C rgb = _TYP StdARGB>
		constexpr static __channel RGB_AlphaBlend(__channel fore, __channel back, __channel alphaF, __channel alphaB) {
			constexpr auto alpha_bitcount = rgb::A::count;
			constexpr auto alpha_bitmax = rgb::A::filter;
			auto alpha_blend = RGB_AlphaBlend<rgb>(alphaF, alphaB);

			return ((fore * alphaF + (back * alphaB * (alpha_bitmax - alphaF) >> alpha_bitcount)) * alpha_blend) >> (alpha_bitcount << 1);
		}

		template<_CPT ARGB_C rgb = _TYP StdARGB>
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

template<_CPT ARGB_C rgb>
struct RGB_Default {
	inline constexpr static typename rgb::type
		white = rgb(0xFF, 0xFF, 0xFF, 0xFF),//白色
		black = rgb(0xFF, 0x00, 0x00, 0x00),//黑色
		red = rgb(0xFF, 0xFF, 0x00, 0x00),//红色
		green = rgb(0xFF, 0x00, 0xFF, 0x00),//绿色
		blue = rgb(0xFF, 0x00, 0x00, 0xFF),//蓝色
		cyan = rgb(0xFF, 0x00, 0xFF, 0xFF),//青色
		purple = rgb(0xFF, 0xFF, 0x00, 0xFF),//紫色
		yellow = rgb(0xFF, 0xFF, 0xFF, 0x00),//黄色
		gray = rgb(0xFF, 0xC0, 0xC0, 0xC0),//灰色
		orange = rgb(0xFF, 0xFF, 0x61, 0x00),//橙色
		turquoise = rgb(0xFF, 0x40, 0xE0, 0xD0),//青蓝色
		pink = rgb(0xFF, 0xFF, 0xC0, 0xCB),//粉色
		transparency = rgb(0x00, 0x00, 0x00, 0x00)//透明
		;
};



NGS_END