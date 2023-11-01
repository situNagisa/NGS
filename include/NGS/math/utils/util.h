#pragma  once

#include "NGS/base/base.h"

NGS_BEGIN

//inline constexpr auto Abs(auto v) { return ::abs(v); }
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

#undef max
#undef min

constexpr auto max(auto a, auto b) { return a > b ? a : b; }
constexpr auto min(auto a, auto b) { return a > b ? b : a; }


/* 判断点是否在区间内 */
template<cpt::real_number T>
bool In(T val, T low, T high) { return val >= low && val <= high; }

/* 判断点是否在区间内 */
template< cpt::real_number T>
bool Between(T val, T low, T high) { return val > low && val < high; }

/* 点与区间的距离，若在区间内则为0 */
template< cpt::real_number T> T Distance(T val, T min, T max) { return max(0, max(min - val, val - max)); }
/* 判断两区间是否相交 */
template< cpt::real_number T> bool IsCross(T min0, T max0, T min1, T max1) { return min1 <= max0 && min0 <= max1; }

template< cpt::real_number T> T Clamp(T value, T low, T high) { return max(low, min(value, high)); }
template< cpt::real_number T> constexpr T NearTo(T value, T aim, T speed) {
	if (value < aim)
		return (value + speed > aim) ? aim : value + speed;
	if (value > aim)
		return (value - speed < aim) ? aim : value - speed;
}

constexpr int8 sign(int64 number) { return -static_cast<int64>((static_cast<byte_<sizeof(int64)>>(number) >> (bit::as_bit<int64>() - 1)) << 1) + 1; }
constexpr int8 sign(float64 floating) { return floating >= 0 ? 1 : -1; }
constexpr int8 sign(bool b) { return (b << 1) - 1; }

inline constexpr auto _degrees_to_radian = std::numbers::pi / 180;
inline constexpr auto _radian_to_degrees = 180 / std::numbers::pi;

constexpr auto decimals(CArithmetic auto floating) {
	return floating - static_cast<int64>(floating);
}

consteval auto round(CArithmetic auto floating) {
	constexpr auto d = decimals(floating);
	if constexpr (d > 0.4) {
		return static_cast<int64>(floating) + 1;
	}
	else {
		return static_cast<int64>(floating);
	}
}

constexpr auto as_radian(auto degree) { return degree * _degrees_to_radian; }
constexpr auto as_degree(auto radian) { return (radian * _radian_to_degrees); }

inline double angle_difference(double angle1, double angle2) {
	double difference = fmod((angle1 - angle2), 2 * std::numbers::pi);
	if (difference > std::numbers::pi) {
		difference -= 2 * std::numbers::pi;
	}
	else if (difference <= -std::numbers::pi) {
		difference += 2 * std::numbers::pi;
	}
	return difference;
}


constexpr auto average(std::integral auto a, std::integral auto b) { return (a & b) + ((a ^ b) >> 1); }

NGS_END