#pragma once

#include "NGS/math/defined.h"
#include "NGS/math/util.h"
#include "NGS/math/geometry/point.h"

NGS_MATH_BEGIN

template<cpt::real_number _ElementType>
struct NGS_DLL_API Rectangle3D {
protected:
	using self_type = Rectangle3D;
public:
	using element_type = _ElementType;
	using point_type = Point3<element_type>;


public:
	constexpr element_type Area()const;
	constexpr bool Empty()const;

	constexpr point_type LeftTop()const;
	constexpr point_type RightTop()const;
	constexpr point_type RightBottom()const;
	constexpr point_type LeftBottom()const;

	constexpr point_type Center()const;

public:
	point_type normal{};
	point_type position{};
	element_type theta = static_cast<element_type>(0);
	element_type width = static_cast<element_type>(0);
	element_type height = static_cast<element_type>(0);
};

NGS_MATH_END
