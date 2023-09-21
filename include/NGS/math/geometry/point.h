#pragma once

#include "NGS/math/mla/vector.h"
#include "NGS/math/defined.h"

NGS_MATH_BEGIN

template<class  _ElementType>
struct NGS_API Point2 : mla::VectorContainer<Point2<_ElementType>, std::integral_constant<size_t, 2>, _ElementType> {
	NGS_menvironment(Point2);
public:
	NGS_minherit_t(element_type, base_type);
	NGS_minherit_t(expression_type, base_type);

	using base_type::base_type;
	constexpr Point2(element_type x, element_type y)
		: x(x)
		, y(y)
	{}
	constexpr Point2() = default;
	template<mla::CVectorExpression _Expression>
		requires (base_type::dimension <= _Expression::expression_type::dimension)
	constexpr Point2(const _Expression& expression)
		: x(expression()(0))
		, y(expression()(1))
	{}

	using base_type::operator();
	using base_type::assign;
	constexpr expression_type& assign(size_t index, element_type element) {
		if (index == 0) {
			x = element;
		}
		else if (index == 1) {
			y = element;
		}
		return (*this)();
	}

	constexpr element_type& operator()(size_t i) {
		if (i == 0)
			return x;
		else if (i == 1)
			return y;
		return x;
	}
	constexpr element_type operator()(size_t i)const {
		if (i == 0)
			return x;
		else if (i == 1)
			return y;
		return 0;
	}

	constexpr float64 Tan()const { return y / x; }
	constexpr float64 Cot()const { return x / y; }
	constexpr float64 Sin()const { return y / mla::modulus(*this); }
	constexpr float64 Cos()const { return x / mla::modulus(*this); }

	float64 ArcTan()const { return std::atan2(y, x); }
	float64 ArcCot()const { return std::atan2(x, y); }
	float64 ArcSin()const { return std::asin(Sin()); }
	float64 ArcCos()const { return std::acos(Cos()); }

	//====================
	// compatibility
	//====================

	constexpr auto Length()const { return mla::modulus(*this); }
	constexpr auto LengthSquared()const { return mla::modulus_squared(*this); }

	void Set(element_type x, element_type y) {
		this->x = x;
		this->y = y;
	}

	constexpr element_type* data() { return &x; }
	constexpr const element_type* data()const { return &x; }
public:
	element_type x = 0;
	element_type y = 0;
};
NGS_CCPT_VERIFY(mla::CVectorContainer, Point2<int>);

using Point2i = Point2<int>;
using Point2u = Point2<unsigned int>;
using Point2f = Point2<float>;
using Point2d = Point2<double>;
using Point2s = Point2<size_t>;


template<class  _ElementType>
struct NGS_API Point3 : mla::VectorContainer<Point3<_ElementType>, std::integral_constant<size_t, 3>, _ElementType> {
	NGS_menvironment(Point3);
public:
	NGS_minherit_t(element_type, base_type);
	NGS_minherit_t(expression_type, base_type);

	using base_type::base_type;
	constexpr Point3(element_type x, element_type y, element_type z)
		: x(x)
		, y(y)
		, z(z)
	{}
	constexpr Point3() = default;

	template<mla::CVectorExpression _Expression>
		requires (base_type::dimension <= _Expression::expression_type::dimension)
	constexpr Point3(const _Expression& expression)
		: Point3(expression()(0), expression()(1), expression()(2))
	{}

	using base_type::assign;
	constexpr expression_type& assign(size_t index, element_type element) {
		if (index == 0) {
			x = element;
		}
		else if (index == 1) {
			y = element;
		}
		else if (index == 2) {
			z = element;
		}
		return (*this)();
	}

	using base_type::operator();
	constexpr element_type& operator()(size_t i) {
		if (i == 0) {
			return x;
		}
		if (i == 1) {
			return y;
		}
		if (i == 2) {
			return z;
		}
		return x;
	}
	constexpr element_type operator()(size_t i)const {
		if (i == 0) {
			return x;
		}
		if (i == 1) {
			return y;
		}
		if (i == 2) {
			return z;
		}
		return 0;
	}

	constexpr element_type* data() { return &x; }
	constexpr const element_type* data()const { return &x; }

	element_type x = 0;
	element_type y = 0;
	element_type z = 0;
};
NGS_CCPT_VERIFY(mla::CVectorContainer, Point3<int>);

using Point3i = Point3<int>;
using Point3u = Point3<unsigned int>;
using Point3f = Point3<float>;
using Point3d = Point3<double>;
using Point3s = Point3<size_t>;

NGS_MATH_END
