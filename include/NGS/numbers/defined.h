#pragma once

#include "NGS/basic/basic.h"
#include "NGS/concept/concept.h"

#define NGS_NUMBERS_BEGIN NGS_BEGIN namespace numbers{
#define NGS_NUMBERS_END } NGS_END

NGS_NUMBERS_BEGIN

template<class T>
struct _invalid_number
{
	static_assert(concepts::none<T>, "Invalid number type");
};

NGS_NUMBERS_END

#define NGS_NUMBERS_DEFINE_CONSTANT(id,value)			\
NGS_NUMBERS_BEGIN										\
template<class T>										\
inline constexpr T id##_v = _invalid_number<T>{};		\
template<::std::floating_point T>						\
inline constexpr T id##_v<T> = static_cast<T>(value);	\
inline constexpr double id = id##_v<double>;			\
NGS_NUMBERS_END											\
//