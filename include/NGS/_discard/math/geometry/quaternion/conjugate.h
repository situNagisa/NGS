#pragma once

#include "NGS/math/geometry/quaternion/quaternion.h"

NGS_MATH_BEGIN

template<CQuaternion _Quaternion>
constexpr auto conjugate(const _Quaternion& quaternion) {
	using quaternion_type = _Quaternion;
	return quaternion_type(mla::negate(quaternion.v), quaternion.w);
}

template<CQuaternion _Quaternion>
constexpr auto operator~(const _Quaternion& quaternion) {
	return conjugate(quaternion);
}

NGS_MATH_END
