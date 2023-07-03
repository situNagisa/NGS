#pragma  once

#include "NGS/base/base.h"

#undef RGB

NGS_BEGIN

enum class PixelFormat : ngs::uint32 {
	unknown,

	ARGB8,
	ARGB15,
	ARGB16,
	ARGB24,
	ARGB32,

	MJPEG,

	YUYV,
};

NGS_CONCEPT

template<typename T>
concept CChannel = requires(T t) {
	{ T::Count } -> std::convertible_to<size_t>;
	{ T::Offset } -> std::convertible_to<size_t>;
	{ T::Filter } -> std::convertible_to<size_t>;
	{ T::FilterWithOffset } -> std::convertible_to<size_t>;
	std::is_integral_v<typename T::type>;
};
NGS_END

NGS_TYPE
template<size_t _Count, size_t _Offset = 0>
struct Channel {
	static constexpr size_t Count = _Count;
	static constexpr size_t Offset = _Offset;

	using type = BitSet<Count>::type;

	static constexpr type Filter = BitSet<Count>::Mask;
	static constexpr  size_t FilterWithOffset = Filter << Offset;

	static constexpr float64 Percent(type value) {
		return static_cast<float64>(value) / Filter;
	}

	template<CChannel _Channel>
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
	template<CChannel _Channel>
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

	static constexpr auto FilterColor(CIntegral auto color) {
		return (color >> Offset) & Filter;
	}
private:
	Channel() = default;
};
using Channel0 = Channel<0>;
using Channel1 = Channel<1>;
using Channel2 = Channel<2>;
using Channel3 = Channel<3>;
using Channel4 = Channel<4>;
using Channel5 = Channel<5>;
using Channel6 = Channel<6>;
using Channel7 = Channel<7>;
using Channel8 = Channel<8>;

using StdChannel = Channel8;

static_assert(CChannel<StdChannel>);
NGS_END

NGS_CONCEPT
template<typename T>
concept CARGB = requires(T t) {
	{ t.Alpha() } -> std::convertible_to<typename T::A::type>;
	{ t.Red() } -> std::convertible_to<typename T::R::type>;
	{ t.Green() } -> std::convertible_to<typename T::G::type>;
	{ t.Blue() } -> std::convertible_to<typename T::B::type>;
	{ t.StdAlpha() } -> std::convertible_to<StdChannel::type>;
	{ t.StdRed() } -> std::convertible_to<StdChannel::type>;
	{ t.StdGreen() } -> std::convertible_to<StdChannel::type>;
	{ t.StdBlue() } -> std::convertible_to<StdChannel::type>;

		requires CChannel<typename T::A>;
		requires CChannel<typename T::R>;
		requires CChannel<typename T::G>;
		requires CChannel<typename T::B>;
		requires std::integral<typename T::type>;
};
NGS_END

NGS_TYPE
#undef _A
#undef _R
#undef _G
#undef _B

#if NGS_PLATFORM == NGS_MSVC
#pragma warning(push)
#pragma warning(disable:4309)
#endif
template<CChannel _A, CChannel _R, CChannel _G, CChannel _B>
struct _basic_ARGB {
public:
	using A = _A;
	using R = _R;
	using G = _G;
	using B = _B;
	using type = byte_<BitSet<A::Count + R::Count + G::Count + B::Count>::ByteCount>;

	using std_type = byte_<BitSet<StdChannel::Count>::ByteCount * 4>;

	static constexpr uint32
		Filter = A::FilterWithOffset | R::FilterWithOffset | G::FilterWithOffset | B::FilterWithOffset
		;

	constexpr _basic_ARGB() = default;
	constexpr _basic_ARGB(type value) : _value(value) {}
	template<CChannel A, CChannel R, CChannel G, CChannel B>
	constexpr _basic_ARGB(_basic_ARGB<A, R, G, B> color)
		: _basic_ARGB(
			(A::template ConvertFrom<StdChannel>(color.StdAlpha()) << A::Offset) |
			(R::template ConvertFrom<StdChannel>(color.StdRed()) << R::Offset) |
			(G::template ConvertFrom<StdChannel>(color.StdGreen()) << G::Offset) |
			(B::template ConvertFrom<StdChannel>(color.StdBlue()) << B::Offset)
		)
	{}

	operator type()const { return _value; }
	constexpr type Value()const { return _value; }

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


	template<_NGS_CPT CChannel _A2, _NGS_CPT CChannel _R2, _NGS_CPT CChannel _G2, _NGS_CPT CChannel _B2>
	constexpr operator _basic_ARGB<_A2, _R2, _G2, _B2>()const {
		return _basic_ARGB<_A2, _R2, _G2, _B2>(
			StdAlpha(),
			StdRed(),
			StdGreen(),
			StdBlue()
		);
	}
private:
	type _value;
};

#define NGS_DEFINE_ARGB(c1,c2,c3,c4)		\
template<size_t _##c1, size_t _##c2, size_t _##c3, size_t _##c4> \
struct c1##c2##c3##c4 : public _basic_ARGB<Channel<_##c1, _##c2 + _##c3 + _##c4>, Channel<_##c2, _##c3 + _##c4>, Channel<_##c3, _##c4>, Channel<_##c4, 0>> { \
	using base = _basic_ARGB<Channel<_##c1, _##c2 + _##c3 + _##c4>, Channel<_##c2, _##c3 + _##c4>, Channel<_##c3, _##c4>, Channel<_##c4, 0>>; \
	using A = typename base::A;				\
	using R = typename base::R;				\
	using G = typename base::G;				\
	using B = typename base::B;				\
	using base::_basic_ARGB;				\
	constexpr c1##c2##c3##c4(				\
		StdChannel::type c1##_,				\
		StdChannel::type c2##_,				\
		StdChannel::type c3##_,				\
		StdChannel::type c4##_				\
	)										\
	: base(\
		(A::template ConvertFrom<StdChannel>(A_) << A::Offset) | \
		(R::template ConvertFrom<StdChannel>(R_) << R::Offset) | \
		(G::template ConvertFrom<StdChannel>(G_) << G::Offset) | \
		(B::template ConvertFrom<StdChannel>(B_) << B::Offset) \
		)									\
	{}										\
};											\
using c1##c2##c3##c4##32 = c1##c2##c3##c4<8, 8, 8, 8>;	\
using c1##c2##c3##c4##24 = c1##c2##c3##c4<0, 8, 8, 8>;	\
using c1##c2##c3##c4##16 = c1##c2##c3##c4<0, 5, 6, 5>;	\
using c1##c2##c3##c4##15 = c1##c2##c3##c4<1, 5, 5, 5>;	\
using c1##c2##c3##c4##8 = c1##c2##c3##c4<0, 3, 3, 2>;	\
using Std##c1##c2##c3##c4 = c1##c2##c3##c4##32;			\
static_assert(_NGS_CPT CARGB<Std##c1##c2##c3##c4>)		\
//

NGS_DEFINE_ARGB(A, R, G, B);
NGS_DEFINE_ARGB(A, R, B, G);
NGS_DEFINE_ARGB(A, G, R, B);
NGS_DEFINE_ARGB(A, G, B, R);
NGS_DEFINE_ARGB(A, B, R, G);
NGS_DEFINE_ARGB(A, B, G, R);

NGS_DEFINE_ARGB(R, A, G, B);
NGS_DEFINE_ARGB(R, A, B, G);
NGS_DEFINE_ARGB(R, G, A, B);
NGS_DEFINE_ARGB(R, G, B, A);
NGS_DEFINE_ARGB(R, B, A, G);
NGS_DEFINE_ARGB(R, B, G, A);

NGS_DEFINE_ARGB(G, A, R, B);
NGS_DEFINE_ARGB(G, A, B, R);
NGS_DEFINE_ARGB(G, R, A, B);
NGS_DEFINE_ARGB(G, R, B, A);
NGS_DEFINE_ARGB(G, B, A, R);
NGS_DEFINE_ARGB(G, B, R, A);

NGS_DEFINE_ARGB(B, A, R, G);
NGS_DEFINE_ARGB(B, A, G, R);
NGS_DEFINE_ARGB(B, R, A, G);
NGS_DEFINE_ARGB(B, R, G, A);
NGS_DEFINE_ARGB(B, G, A, R);
NGS_DEFINE_ARGB(B, G, R, A);

#undef NGS_DEFINE_ARGB


struct HSV {
	using HueType = byte;
	constexpr static auto HueRate = (BitSet<sizeof(HueType) * BitPerByte>::Mask) >= 360 ? 2 : 1;

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

class Color {
public:
	NGS_TYPE_DEFINE(uint8, channel);

	struct Blend {
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
	template<class _Color>
	constexpr auto white = _Color(StdARGB(0xFF, 0xFF, 0xFF, 0xFF));//白色
	template<class _Color>
	constexpr auto black = _Color(StdARGB(0xFF, 0x00, 0x00, 0x00));//黑色
	template<class _Color>
	constexpr auto red = _Color(StdARGB(0xFF, 0xFF, 0x00, 0x00));//红色
	template<class _Color>
	constexpr auto green = _Color(StdARGB(0xFF, 0x00, 0xFF, 0x00));//绿色
	template<class _Color>
	constexpr auto blue = _Color(StdARGB(0xFF, 0x00, 0x00, 0xFF));//蓝色
	template<class _Color>
	constexpr auto cyan = _Color(StdARGB(0xFF, 0x00, 0xFF, 0xFF));//青色
	template<class _Color>
	constexpr auto purple = _Color(StdARGB(0xFF, 0xFF, 0x00, 0xFF));//紫色
	template<class _Color>
	constexpr auto yellow = _Color(StdARGB(0xFF, 0xFF, 0xFF, 0x00));//黄色
	template<class _Color>
	constexpr auto gray = _Color(StdARGB(0xFF, 0x80, 0x80, 0x80));//灰色
	template<class _Color>
	constexpr auto lightgray = _Color(StdARGB(0xFF, 0xC0, 0xC0, 0xC0));//浅灰色
	template<class _Color>
	constexpr auto darkgray = _Color(StdARGB(0xFF, 0x40, 0x40, 0x40));//深灰色
	template<class _Color>
	constexpr auto transparent = _Color(StdARGB(0x00, 0x00, 0x00, 0x00));//透明色
}

using ColorConvert = mpl::bitmap<PixelFormat,
	mpl::bitmap_item<ARGB8, (uint32)PixelFormat::ARGB8 >,
	mpl::bitmap_item<ARGB15, (uint32)PixelFormat::ARGB15>,
	mpl::bitmap_item<ARGB16, (uint32)PixelFormat::ARGB16>,
	mpl::bitmap_item<ARGB24, (uint32)PixelFormat::ARGB24>,
	mpl::bitmap_item<ARGB32, (uint32)PixelFormat::ARGB32>
>;

#if NGS_PLATFORM == NGS_MSVC
#pragma warning(pop)
#endif

NGS_END