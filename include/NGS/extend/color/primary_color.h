#pragma once

#include "NGS/extend/color/defined.h"
#include "NGS/extend/color/channel.h"

#undef RGB

NGS_BEGIN
NGS_CONCEPT

template<typename T>
concept CPrimaryColor = requires(T t) {
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
NGS_END

NGS_COLOR_SPACE_BEGIN

#undef _A
#undef _R
#undef _G
#undef _B

#if NGS_PLATFORM == NGS_MSVC
#pragma warning(push)
#pragma warning(disable:4309)
#endif

template<CChannel _A, CChannel _R, CChannel _G, CChannel _B>
struct PrimaryColor {
public:
	using A = _A;
	using R = _R;
	using G = _G;
	using B = _B;
	using type = byte_<bit::as_byte(A::Count + R::Count + G::Count + B::Count)>;

	using std_type = byte_<bit::as_byte(StdChannel::Count) * 4>;

	static constexpr uint32
		Filter = A::FilterWithOffset | R::FilterWithOffset | G::FilterWithOffset | B::FilterWithOffset
		;
	static constexpr PixelFormat Format{
		.size = bit::as_byte(A::Count + R::Count + G::Count + B::Count),
	};

	constexpr PrimaryColor() = default;
	constexpr PrimaryColor(type value) : _value(value) {}
	template<CChannel A, CChannel R, CChannel G, CChannel B>
	constexpr PrimaryColor(PrimaryColor<A, R, G, B> color)
		: PrimaryColor(
			(A::template ConvertFrom<StdChannel>(color.StdAlpha()) << A::Offset) |
			(R::template ConvertFrom<StdChannel>(color.StdRed()) << R::Offset) |
			(G::template ConvertFrom<StdChannel>(color.StdGreen()) << G::Offset) |
			(B::template ConvertFrom<StdChannel>(color.StdBlue()) << B::Offset)
		)
	{}

	template<CChannel A, CChannel R, CChannel G, CChannel B>
	PrimaryColor& operator=(const PrimaryColor<A, R, G, B>& color) {
		_value =
			(A::template ConvertFrom<StdChannel>(color.StdAlpha()) << A::Offset) |
			(R::template ConvertFrom<StdChannel>(color.StdRed()) << R::Offset) |
			(G::template ConvertFrom<StdChannel>(color.StdGreen()) << G::Offset) |
			(B::template ConvertFrom<StdChannel>(color.StdBlue()) << B::Offset);
	}

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
	constexpr operator PrimaryColor<_A2, _R2, _G2, _B2>()const {
		return PrimaryColor<_A2, _R2, _G2, _B2>(
			StdAlpha(),
			StdRed(),
			StdGreen(),
			StdBlue()
		);
	}
private:
	type _value{};
};

#define NGS_DEFINE_ARGB(c1,c2,c3,c4)		\
template<size_t _##c1, size_t _##c2, size_t _##c3, size_t _##c4> \
struct c1##c2##c3##c4 : public PrimaryColor<Channel<_##c1, _##c2 + _##c3 + _##c4>, Channel<_##c2, _##c3 + _##c4>, Channel<_##c3, _##c4>, Channel<_##c4, 0>> { \
	using base = PrimaryColor<Channel<_##c1, _##c2 + _##c3 + _##c4>, Channel<_##c2, _##c3 + _##c4>, Channel<_##c3, _##c4>, Channel<_##c4, 0>>; \
	using A = typename base::A;				\
	using R = typename base::R;				\
	using G = typename base::G;				\
	using B = typename base::B;				\
	using base::PrimaryColor;				\
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

#if NGS_PLATFORM == NGS_MSVC
#pragma warning(pop)
#endif

NGS_COLOR_SPACE_END
