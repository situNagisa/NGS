#pragma once

#include "NGS/math/geometry/quaternion/quaternion.h"

NGS_MATH_BEGIN

//=====================
// 这里的requires语句是为了达到`不可分割约束`，
// 即为了与mla中的multiplies函数能够区分开
//=====================

template<CQuaternion _Quaternion1,CQuaternion _Quaternion2> requires mla::CVectorSameDimension<_Quaternion1, _Quaternion2>
constexpr auto multiplies(const _Quaternion1& q1, const _Quaternion2& q2) {
	using element_type = mpl::promote_t<typename _Quaternion1::element_type, typename _Quaternion2::element_type>;
	using quaternion_type = Quaternion<element_type>;

	return quaternion_type(
		mla::multiplies_scalar(q1.w, q2.v) +
		mla::multiplies_scalar(q2.w, q1.v) +
		mla::product_outer(q1.v, q2.v),
		q1.w * q2.w - mla::product_inner(q1.v, q2.v)
	);
}

template<CQuaternion _Quaternion1, CQuaternion _Quaternion2> requires mla::CVectorSameDimension<_Quaternion1, _Quaternion2>
constexpr auto operator*(const _Quaternion1& q1, const _Quaternion2& q2) {
	return multiplies(q1, q2);
}

NGS_MATH_END
