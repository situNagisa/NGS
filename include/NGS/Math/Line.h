#pragma once

#include "NGS/base/base.h"
#include "NGS/math/vector.h"

NGS_BEGIN

template<_CPT Arithmetic Number>
class Line2D {
public:
	constexpr Line2D() = default;
	constexpr Line2D(const Point2_<Number>& A, const Point2_<Number>& B)
		: A(A)
		, B(B)
	{}
	constexpr Line2D(Number x1, Number y1, Number x2, Number y2)
		: A(x1, y1)
		, B(x2, y2)
	{}
public:

private:

public:
	Point2_<Number>
		A, B;
};

using Line2i = Line2D<int>;
using Line2d = Line2i;
using Line2f = Line2D<float>;
using Line2lf = Line2D<double>;

using Line2 = Line2i;

NGS_END
