#include "defined.h"

USE_NGS;

TEST(color, argb) {
	constexpr auto c5 = Channel5::ConvertFrom<Channel8>(0x40);

	constexpr ARGB8 argb8(0xFF, 0xFF, 0x80, 0x40);
	constexpr auto a8 = argb8.Alpha();
	constexpr auto r8 = argb8.Red();
	constexpr auto g8 = argb8.Green();
	constexpr auto b8 = argb8.Blue();
	constexpr auto sa8 = argb8.StdAlpha();
	constexpr auto sr8 = argb8.StdRed();
	constexpr auto sg8 = argb8.StdGreen();
	constexpr auto sb8 = argb8.StdBlue();

	constexpr BGRA8 bgra8(0x40, 0x80, 0xFF, 0xFF);
	constexpr auto b8_ = bgra8.Blue();
	constexpr auto g8_ = bgra8.Green();
	constexpr auto r8_ = bgra8.Red();
	constexpr auto a8_ = bgra8.Alpha();
	constexpr auto sb8_ = bgra8.StdBlue();
	constexpr auto sg8_ = bgra8.StdGreen();
	constexpr auto sr8_ = bgra8.StdRed();
	constexpr auto sa8_ = bgra8.StdAlpha();

	static_assert(a8 == a8_);
	static_assert(r8 == r8_);
	static_assert(g8 == g8_);
	static_assert(b8 == b8_);
	static_assert(sa8 == sa8_);
	static_assert(sr8 == sr8_);
	static_assert(sg8 == sg8_);
	static_assert(sb8 == sb8_);


	constexpr ARGB16 argb16(0xFF, 0xFF, 0x80, 0x40);
	constexpr auto a16 = argb16.Alpha();
	constexpr auto r16 = argb16.Red();
	constexpr auto g16 = argb16.Green();
	constexpr auto b16 = argb16.Blue();
	constexpr auto sa16 = argb16.StdAlpha();
	constexpr auto sr16 = argb16.StdRed();
	constexpr auto sg16 = argb16.StdGreen();
	constexpr auto sb16 = argb16.StdBlue();

	constexpr BGRA16 bgra16(0x40, 0x80, 0xFF, 0xFF);
	constexpr auto b16_ = bgra16.Blue();
	constexpr auto g16_ = bgra16.Green();
	constexpr auto r16_ = bgra16.Red();
	constexpr auto a16_ = bgra16.Alpha();
	constexpr auto sb16_ = bgra16.StdBlue();
	constexpr auto sg16_ = bgra16.StdGreen();
	constexpr auto sr16_ = bgra16.StdRed();
	constexpr auto sa16_ = bgra16.StdAlpha();

	static_assert(a16 == a16_);
	static_assert(r16 == r16_);
	static_assert(g16 == g16_);
	static_assert(b16 == b16_);
	static_assert(sa16 == sa16_);
	static_assert(sr16 == sr16_);
	static_assert(sg16 == sg16_);
	static_assert(sb16 == sb16_);

	constexpr ARGB32 argb32(0xFF, 0xFF, 0x80, 0x40);
	constexpr auto a32 = argb32.Alpha();
	constexpr auto r32 = argb32.Red();
	constexpr auto g32 = argb32.Green();
	constexpr auto b32 = argb32.Blue();
}
