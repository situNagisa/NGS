#pragma  once

#include "NGS/NGS_Defined.h"
#include "NGS/NGS_STL.h"
#include "NGS/NGS_Concepts.h"
#include "NGS/NGS_Bit.h"

NGS_BEGIN

inline constexpr auto Abs(auto v) { return ::abs(v); }
/*
int abs(int n)
{
  return (n ^ (n >> 31)) - (n >> 31);
}

int abs(int n)
{
  int const mask = n >> (sizeof(int) * CHAR_BIT - 1);
  return (n + mask) ^ mask;
}

int abs(int n)
{
  int i = n >> 31;
  return i == 0 ? n : (~n + 1);
}

*/

inline auto Max(auto a, auto b) { return a > b ? a : b; }
inline auto Min(auto a, auto b) { return a > b ? b : a; }


/* 判断点是否在区间内 */
template<_CPT Arithmetic T>
bool In(T val, T low, T high) { return val >= low && val <= high; }

/* 判断点是否在区间内 */
template<_CPT Arithmetic T>
bool Between(T val, T low, T high) { return val > low && val < high; }

/* 点与区间的距离，若在区间内则为0 */
template<_CPT Arithmetic T>inline T Distance(T val, T min, T max) { return Max(0, Max(min - val, val - max)); }
/* 判断两区间是否相交 */
template<_CPT Arithmetic T>inline bool IsCross(T min0, T max0, T min1, T max1) { return min1 <= max0 && min0 <= max1; }

template<_CPT Arithmetic T>inline T Clamp(T value, T low, T high) { return Max(low, Min(value, high)); }
template<_CPT Arithmetic T>inline constexpr T NearTo(T value, T aim, T speed) {
	if (value < aim)
		return (value + speed > aim) ? aim : value + speed;
	if (value > aim)
		return (value - speed < aim) ? aim : value - speed;
}
template<_CPT SignedIntegral T>
constexpr int8 Sign(T number) { return -(T)(((byte_<sizeof(T)>)number >> (BitsOf<T>() - 1)) << 1) + 1; }
template<_CPT FloatingPoint T>
constexpr int8 Sign(T floating) { return floating >= 0 ? 1 : -1; }
constexpr int8 Sign(bool b) { return (b << 1) - 1; }

inline constexpr const float PI = 3.1415926f;
inline static constexpr float _degrees_to_radian = PI / 180;
inline static constexpr float _radian_to_degrees = 180 / PI;

auto Sin(_CPT Arithmetic auto radian) { return ::sin(radian); }
auto Cos(_CPT Arithmetic auto radian) { return ::cos(radian); }
auto Tan(_CPT Arithmetic auto radian) { return ::tan(radian); }

constexpr auto Decimals(_CPT Arithmetic auto floating) {
	return floating - int64(floating);
}
consteval auto Power(_CPT Arithmetic auto value, size_t power) {
	switch (power)
	{
	case 0:
		return 1;
		break;
	case 1:
		break;
	default:
		for (size_t i = 1; i < power; i++)
			value *= value;
		break;
	}
	return value;
}
consteval auto Round(_CPT Arithmetic auto floating) {
	constexpr auto d = floating - int64(floating);
	if constexpr (d > 0.4) {
		return int64(floating) + 1;
	}
	else {
		return int64(floating);
	}
}
inline constexpr auto Floor(_CPT Arithmetic auto floating) { return ::floor(floating); }
inline constexpr auto Ceil(_CPT Arithmetic auto floating) { return ::ceil(floating); }

inline constexpr float AsRadian(int32 degree) { return degree * _degrees_to_radian; }
inline constexpr int32 AsDegree(float radian) { return static_cast<int32>(radian * _radian_to_degrees); }

constexpr auto Average(_CPT Integral auto a, _CPT Integral auto b) { return (a & b) + ((a ^ b) >> 1); }

template <typename T>
constexpr T Sqrt(T x) {
	return std::sqrt(x);
	// if constexpr (std::is_constant_evaluated()) {
	// 	/*static_assert(x >= 0, "Sqrt argument must be non-negative");
	// 	auto SqrtHelper = [&](T curr, T prev) constexpr {
	// 		return curr == prev ? curr : SqrtHelper(0.5 * (curr + x / curr), curr);
	// 	};
	// 	return SqrtHelper(x, 0);*/
	// 	return std::sqrt(x);
	// }
	// else {
	// 	return std::sqrt(x);
	// }
}

NGS_END