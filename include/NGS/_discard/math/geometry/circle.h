#pragma once

#include "NGS/math/defined.h"
#include "NGS/math/geometry/point.h"

NGS_MATH_BEGIN

template<class _ElementType>
struct NGS_DLL_API Circle {
private:
	using self_type = Circle;
public:
	using element_type = _ElementType;
	using point_type = Point2<element_type>;

	Circle() = default;
	Circle(const self_type&) = default;
	Circle(element_type x,element_type y,element_type radius)
		: position(x,y)
		, radius(radius)
	{}
	Circle(const point_type& position,element_type radius)
		: position(position)
		, radius(radius)
	{}

	void Set(element_type x, element_type y, element_type radius) {
		position.Set(x, y);
		this->radius = radius;
	}
	void Set(const point_type& position, element_type radius) {
		this->position = position;
		this->radius = radius;
	}
	void Set(const self_type& other) {
		position = other.position;
		radius = other.radius;
	}

	self_type& Assign(element_type x, element_type y, element_type radius) {
		Set(x, y, radius);
		return *this;
	}
	self_type& Assign(const self_type& other) { return (*this) = other; }

	point_type position{};
	element_type radius{};
};

using Circlei = Circle<int>;
using Circlef = Circle<float>;
using Circled = Circle<double>;

NGS_MATH_END
