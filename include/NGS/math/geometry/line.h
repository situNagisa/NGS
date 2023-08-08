#pragma once

#include "NGS/math/defined.h"
#include "NGS/math/geometry/point.h"

NGS_MATH_BEGIN

template<CArithmetic _ElementType>
class Line2 {
public:
	using element_type = _ElementType;
	using point_type = Point2<element_type>;

	constexpr Line2() = default;
	constexpr Line2(const point_type& A, const point_type& B)
		: A(A)
		, B(B)
	{}
	constexpr Line2(element_type x1, element_type y1, element_type x2, element_type y2)
		: A(x1, y1)
		, B(x2, y2)
	{}

public:
	point_type A{};
	point_type B{};
};

using Line2i = Line2<int>;
using Line2f = Line2<float>;
using Line2lf = Line2<double>;

NGS_MATH_END
