#pragma once

#include "./defined.h"

NGS_BEGIN
namespace numbers {

template<class _Type>
inline constexpr bool _always_false = false;

template<class _Type>
struct _InvalidNumber {
	static_assert(_always_false<_Type>, "Invalid number type");
};

#define NGS_DEFINE_CONSTANT_NUMBER(id,value)							\
template<class _Type>													\
inline constexpr _Type id##_v = _InvalidNumber<_Type>{};				\
template<std::floating_point _Float>									\
inline constexpr _Float id##_v<_Float> = static_cast<_Float>(value);	\
inline constexpr double id = id##_v<double>								\
//
NGS_DEFINE_CONSTANT_NUMBER(light_speed, 299792458.0);

#undef NGS_DEFINE_CONSTANT_NUMBER

}
NGS_END
