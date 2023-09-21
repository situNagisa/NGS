#pragma once

#include "NGS/math/defined.h"
#include "NGS/math/mla/vector.h"

NGS_MATH_BEGIN
namespace axis_1 {
template<mla::CScalarExpression _Scalar>
inline constexpr _Scalar x = 1;
}

namespace axis_2 {
template<mla::CScalarExpression _Scalar>
inline constexpr mla::Vector<2, _Scalar> x{ 1,0 };
template<mla::CScalarExpression _Scalar>
inline constexpr mla::Vector<2, _Scalar> y{ 0,1 };
}

namespace axis_3 {
template<mla::CScalarExpression _Scalar>
inline constexpr mla::Vector<3, _Scalar> x{ 1,0,0 };
template<mla::CScalarExpression _Scalar>
inline constexpr mla::Vector<3, _Scalar> y{ 0,1,0 };
template<mla::CScalarExpression _Scalar>
inline constexpr mla::Vector<3, _Scalar> z{ 0,0,1 };
}

namespace axis_4 {
template<mla::CScalarExpression _Scalar>
inline constexpr mla::Vector<4, _Scalar> x{ 1,0,0,0 };
template<mla::CScalarExpression _Scalar>
inline constexpr mla::Vector<4, _Scalar> y{ 0,1,0,0 };
template<mla::CScalarExpression _Scalar>
inline constexpr mla::Vector<4, _Scalar> z{ 0,0,1,0 };
template<mla::CScalarExpression _Scalar>
inline constexpr mla::Vector<4, _Scalar> w{ 0,0,0,1 };
}
NGS_MATH_END
