#pragma once

#include "NGS/math/defined.h"
#include "NGS/math/space/axis.h"
#include "NGS/math/mla/vector.h"

NGS_MATH_BEGIN

template<space::CAxis _Axis,size_t _Dimension,mla::CScalarExpression _ElementType>
constexpr auto base_vector() {
	using vector_type = mla::Vector<_Dimension, _ElementType>;
	vector_type result{};
	result(_Axis::dimension) = _Axis::sign;
	return result;
}

NGS_MATH_END
