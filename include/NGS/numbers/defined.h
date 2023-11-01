#pragma once

#include "NGS/basic/basic.h"
#include "NGS/cpt/cpt.h"

#define NGS_NUMBERS_BEGIN NGS_BEGIN namespace numbers{
#define NGS_NUMBERS_END } NGS_END

NGS_NUMBERS_BEGIN

template<class _Type>
struct _InvalidNumber {
	static_assert(cpt::none<_Type>, "Invalid number type");
};

NGS_NUMBERS_END

#define NGS_NUMBERS_DEFINE_CONSTANT(id,value)							\
NGS_NUMBERS_BEGIN														\
template<class _Type>													\
inline constexpr _Type id##_v = _InvalidNumber<_Type>{};				\
template<std::floating_point _Float>									\
inline constexpr _Float id##_v<_Float> = static_cast<_Float>(value);	\
inline constexpr double id = id##_v<double>;							\
NGS_NUMBERS_END															\
//