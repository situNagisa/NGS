#pragma once

#include "../channel.h"

#undef RGB
#undef _A
#undef _R
#undef _G
#undef _B

NGS_COLOR_BEGIN

template<typename T>
concept CPrimaryColor = requires(T t) {
	{ t.Alpha() } -> std::convertible_to<typename T::A::type>;
	{ t.Red() } -> std::convertible_to<typename T::R::type>;
	{ t.Green() } -> std::convertible_to<typename T::G::type>;
	{ t.Blue() } -> std::convertible_to<typename T::B::type>;

	{ t.StdAlpha() } -> std::convertible_to<standard_channel::type>;
	{ t.StdRed() } -> std::convertible_to<standard_channel::type>;
	{ t.StdGreen() } -> std::convertible_to<standard_channel::type>;
	{ t.StdBlue() } -> std::convertible_to<standard_channel::type>;

		requires CChannel<typename T::A>;
		requires CChannel<typename T::R>;
		requires CChannel<typename T::G>;
		requires CChannel<typename T::B>;
		requires std::integral<typename T::type>;
	//requires CColor<T>;
};




#if NGS_COMPILER == NGS_COMPILER_MSVC
#pragma warning(push)
#pragma warning(disable:4309)
#pragma warning(push)
#pragma warning(disable:4333)
#endif

template<CChannel _A, CChannel _R, CChannel _G, CChannel _B>
struct NGS_DLL_API primary {
protected:
	using self_type = primary;
public:
	using A = _A;
	using R = _R;
	using G = _G;
	using B = _B;

	constexpr static size_t bit_count = A::count + R::count + G::count + B::count;
	constexpr static size_t byte_count = bits::as_byte(bit_count);

	using type = byte_<byte_count>;

	using std_type = byte_<bits::as_byte(standard_channel::count) * 4>;

	static constexpr size_t filter = A::filter_with_offset | R::filter_with_offset | G::filter_with_offset | B::filter_with_offset;
	static constexpr color_format_d format{ .size = byte_count, };

	constexpr primary() = default;
	explicit(false) constexpr primary(type value) : _value(value) {}

	template<CChannel A, CChannel R, CChannel G, CChannel B>
	explicit(false) constexpr primary(const primary<A, R, G, B>& color)
		: primary(
			(A::template convert_from<standard_channel>(color.StdAlpha()) << A::offset) |
			(R::template convert_from<standard_channel>(color.StdRed()) << R::offset) |
			(G::template convert_from<standard_channel>(color.StdGreen()) << G::offset) |
			(B::template convert_from<standard_channel>(color.StdBlue()) << B::offset)
		)
	{}

	template<CChannel A, CChannel R, CChannel G, CChannel B>
	primary& operator=(const primary<A, R, G, B>& color) {
		_value =
			(A::template CONVERT_FROM<StdChannel>(color.StdAlpha()) << A::offset) |
			(R::template CONVERT_FROM<StdChannel>(color.StdRed()) << R::offset) |
			(G::template CONVERT_FROM<StdChannel>(color.StdGreen()) << G::offset) |
			(B::template CONVERT_FROM<StdChannel>(color.StdBlue()) << B::offset);
		return *this;
	}

	/*template<color_channel A, color_channel R, color_channel G, color_channel B>
	explicit(false) constexpr operator primary<A, R, G, B>()const {
		return primary<A, R, G, B>(
			(A::template CONVERT_FROM<StdChannel>(StdAlpha()) << A::offset) |
			(R::template CONVERT_FROM<StdChannel>(StdRed()) << R::offset) |
			(G::template CONVERT_FROM<StdChannel>(StdGreen()) << G::offset) |
			(B::template CONVERT_FROM<StdChannel>(StdBlue()) << B::offset)
		);
	}*/

	explicit(true) operator type()const { return _value; }
	constexpr type Value()const { return _value; }

	constexpr typename A::type Alpha() const { return ((_value >> A::offset) & A::filter); }
	void Alpha(typename A::type a) { _value = ((a << A::offset) & A::filter_with_offset) | (_value & ~A::filter_with_offset); }
	constexpr typename R::type Red() const { return ((_value >> R::offset) & R::filter); }
	void Red(typename R::type r) { _value = ((r << R::offset) & R::filter_with_offset) | (_value & ~R::filter_with_offset); }
	constexpr typename G::type Green() const { return ((_value >> G::offset) & G::filter); }
	void Green(typename G::type g) { _value = ((g << G::offset) & G::filter_with_offset) | (_value & ~G::filter_with_offset); }
	constexpr typename B::type Blue() const { return ((_value >> B::offset) & B::filter); }
	void Blue(typename B::type b) { _value = ((b << B::offset) & B::filter_with_offset) | (_value & ~B::filter_with_offset); }

	constexpr StdChannel::type StdAlpha()const { return A::template CONVERT_TO<StdChannel>(Alpha()); }
	void StdAlpha(StdChannel::type a) { Alpha(A::template CONVERT_FROM<StdChannel>(a)); }
	constexpr StdChannel::type StdRed()const { return R::template CONVERT_TO<StdChannel>(Red()); }
	void StdRed(StdChannel::type r) { Red(R::template CONVERT_FROM<StdChannel>(r)); }
	constexpr StdChannel::type StdGreen()const { return G::template CONVERT_TO<StdChannel>(Green()); }
	void StdGreen(StdChannel::type g) { Green(G::template CONVERT_FROM<StdChannel>(g)); }
	constexpr StdChannel::type StdBlue()const { return B::template CONVERT_TO<StdChannel>(Blue()); }
	void StdBlue(StdChannel::type b) { Blue(B::template CONVERT_FROM<StdChannel>(b)); }

	constexpr auto AlphaPercent()const { return A::PERCENT(Alpha()); }
	constexpr auto RedPercent()const { return R::PERCENT(Red()); }
	constexpr auto GreenPercent()const { return G::PERCENT(Green()); }
	constexpr auto BluePercent()const { return B::PERCENT(Blue()); }



	/*template<color_channel _A2, color_channel _R2, color_channel _G2, color_channel _B2>
	constexpr operator primary<_A2, _R2, _G2, _B2>()const {
		return primary<_A2, _R2, _G2, _B2>(
			StdAlpha(),
			StdRed(),
			StdGreen(),
			StdBlue()
		);
	}*/
private:
	type _value{};
};

#define NGS_DEFINE_ARGB(c1,c2,c3,c4)		\
template<size_t _##c1, size_t _##c2, size_t _##c3, size_t _##c4> \
struct NGS_DLL_API c1##c2##c3##c4 : public primary<Channel<_##c1, _##c2 + _##c3 + _##c4>, Channel<_##c2, _##c3 + _##c4>, Channel<_##c3, _##c4>, Channel<_##c4, 0>> { \
	NGS_MPL_ENVIRON(c1##c2##c3##c4);		\
public:										\
	using A = typename base_type::A;		\
	using R = typename base_type::R;		\
	using G = typename base_type::G;		\
	using B = typename base_type::B;		\
	using base_type::base_type;				\
	constexpr c1##c2##c3##c4(				\
		StdChannel::type c1##_,				\
		StdChannel::type c2##_,				\
		StdChannel::type c3##_,				\
		StdChannel::type c4##_				\
	)										\
	: base_type(\
		(A::template CONVERT_FROM<StdChannel>(A_) << A::offset) | \
		(R::template CONVERT_FROM<StdChannel>(R_) << R::offset) | \
		(G::template CONVERT_FROM<StdChannel>(G_) << G::offset) | \
		(B::template CONVERT_FROM<StdChannel>(B_) << B::offset) \
		)									\
	{}										\
};											\
using c1##c2##c3##c4##32 = c1##c2##c3##c4<8, 8, 8, 8>;	\
using c1##c2##c3##c4##24 = c1##c2##c3##c4<0, 8, 8, 8>;	\
using c1##c2##c3##c4##16 = c1##c2##c3##c4<0, 5, 6, 5>;	\
using c1##c2##c3##c4##15 = c1##c2##c3##c4<1, 5, 5, 5>;	\
using c1##c2##c3##c4##8 = c1##c2##c3##c4<0, 3, 3, 2>;	\
using Std##c1##c2##c3##c4 = c1##c2##c3##c4##32;			\
static_assert(CPrimaryColor<Std##c1##c2##c3##c4>)		\
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

#if NGS_COMPILER == NGS_COMPILER_MSVC
#pragma warning(pop)
#pragma warning(pop)
#endif

template<CPrimaryColor _Color>
struct ColorConstants<_Color> {
	//static constexpr _Color white = ARGB32(0xFFFFFFFF);
	//static constexpr _Color black = ARGB32(0xFF000000);
	//static constexpr _Color red = ARGB32(0xFFFF0000);
	//static constexpr _Color green = ARGB32(0xFF00FF00);
	//static constexpr _Color blue = ARGB32(0xFF0000FF);
	//static constexpr _Color yellow = ARGB32(0xFFFFFF00);
	//static constexpr _Color cyan = ARGB32(0xFF00FFFF);
	//static constexpr _Color magenta = ARGB32(0xFFFF00FF);
	//static constexpr _Color transparent = ARGB32(0x00000000);
};
//NGS_CCPT_VERIFY(CColorConstants, ColorConstants<RGBA32>);

NGS_COLOR_END
