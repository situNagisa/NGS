#pragma  once

#include "NGS/math/defined.h"
#include "NGS/math/util.h"
#include "NGS/math/geometry/point.h"

NGS_MATH_BEGIN

template<CArithmetic _ElementType>
struct Rectangle {
private:
	using self_type = Rectangle;
	using point_type = Point2<_ElementType>;
public:
	using element_type = _ElementType;

	//=============
	// construct
	//=============

	constexpr Rectangle() = default;
	constexpr Rectangle(element_type x, element_type y, element_type width, element_type height) :x(x), y(y), width(width), height(height) {}
	constexpr Rectangle(const point_type& position, const point_type& size) : x(position.x), y(position.y), width(size.x), height(size.y) {}
	constexpr Rectangle(element_type x, element_type y, const point_type& size) : x(x), y(y), width(size.x), height(size.y) {}
	constexpr Rectangle(const point_type& position, element_type width, element_type height) : x(position.x), y(position.y), width(width), height(height) {}
	template<CTemplateFrom<Rectangle> _Rectangle>
	constexpr Rectangle(const _Rectangle& other) : x(other.x), y(other.y), width(other.width), height(other.height) {}

	//=============
	// basic
	//=============

	constexpr element_type Area()const { return width * height; }
	constexpr bool Empty()const { return !Area(); }
	constexpr explicit operator bool()const { return !Empty(); }

	constexpr auto Top() const { return y; }
	constexpr auto Bottom() const { return y + height; }
	constexpr auto Right() const { return x + width; }
	constexpr auto Left() const { return x; }

	constexpr auto LeftTop()const { return point_type(Left(), Top()); }
	constexpr auto LeftBottom()const { return point_type(Left(), Bottom()); }
	constexpr auto RightTop()const { return point_type(Right(), Top()); }
	constexpr auto RightBottom()const { return point_type(Right(), Bottom()); }

	constexpr auto Center()const { return point_type((Left() + Right()) / 2, (Top() + Bottom()) / 2); }

	//===============
	// binary
	//===============

	constexpr friend bool IsIntersect(const self_type& a, const self_type& b) {
		return IsCross(a.Left(), a.Right(), b.Left(), b.Right()) && IsCross(a.Top(), a.Bottom(), b.Top(), b.Bottom());
	}
	constexpr bool IsIntersect(const self_type& other)const { return IsIntersect(*this, other); }

	template<CTemplateFrom<Rectangle> _Rectangle>
	constexpr friend auto Intersect(const self_type& a, const _Rectangle& b) {
		if (!IsIntersect(a, b))return {};
		using result_type = mpl::promote_t<element_type, typename _Rectangle::element_type>;
		return Rectangle<result_type>(
			std::max(a.Left(), b.Left()),
			std::max(a.Top(), b.Top()),
			std::min(a.Right(), b.Right()),
			std::min(a.Bottom(), b.Bottom())
		);
	}
	template<CTemplateFrom<Rectangle> _Rectangle>
	constexpr auto Intersect(const _Rectangle& other)const { return Intersect(*this, other); }
	template<CTemplateFrom<Rectangle> _Rectangle>
	constexpr friend auto operator&(const self_type& a, const _Rectangle& b) { return Intersect(a, b); }
	template<CTemplateFrom<Rectangle> _Rectangle>
	constexpr self_type& operator&=(const _Rectangle& other) { return (*this) = Intersect(*this, other); }

	template<CTemplateFrom<Rectangle> _Rectangle>
	constexpr friend auto Union(const self_type& a, const _Rectangle& b) {
		using result_type = mpl::promote_t<element_type, typename _Rectangle::element_type>;
		return Rectangle<result_type>(
			std::min(a.Left(), b.Left()),
			std::min(a.Top(), b.Top()),
			std::max(a.Right(), b.Right()),
			std::max(a.Bottom(), b.Bottom())
		);
	}
	template<CTemplateFrom<Rectangle> _Rectangle>
	constexpr auto Union(const _Rectangle& other)const { return Union(*this, other); }
	template<CTemplateFrom<Rectangle> _Rectangle>
	constexpr friend auto operator|(const self_type& a, const _Rectangle& b) { return Union(a, b); }
	template<CTemplateFrom<Rectangle> _Rectangle>
	constexpr self_type& operator|=(const _Rectangle& other) { return (*this) = Union(*this, other); }

	constexpr bool Contain(element_type x, element_type y)const { return In(x, Left(), Right()) && In(y, Top(), Bottom()); }
	constexpr bool Contain(const point_type& point)const { return Contain(point.x, point.y); }
	constexpr bool Contain(const self_type& other)const { return Contain(other.LeftTop()) && Contain(other.RightBottom()); }

	template<CTemplateFrom<Rectangle> _Rectangle>
	constexpr bool operator==(const _Rectangle& other)const { return x == other.x && y == other.y && width == other.width && height == other.height; }
	//==============
	// assign
	//==============

	constexpr self_type& Assign(element_type x, element_type y, element_type width, element_type height) {
		this->x = x;
		this->y = y;
		this->width = width;
		this->height = height;
		return *this;
	}
	self_type& Assign(const self_type& other) { return *this = other; }

	void Set(element_type x, element_type y, element_type width, element_type height) { Assign(x, y, width, height); }
	void Set(const self_type& other) { Assign(other); }
	void SetZero() { Assign(0, 0, 0, 0); }
	void Normalize() {
		if (width < 0) {
			x += width;
			width = -width;
		}
		if (height < 0) {
			y += height;
			height = -height;
		}
	}

	constexpr self_type& Translate(element_type x, element_type y) {
		this->x += x;
		this->y += y;
		return *this;
	}
	constexpr self_type& Translate(const point_type& offset) { return Translate(offset.x, offset.y); }
	constexpr self_type& Resize(element_type width, element_type height) {
		this->width += width;
		this->height += height;
		return *this;
	}
	constexpr self_type& Resize(const point_type& size) { return Resize(size.x, size.y); }

public:
	element_type x = 0;
	element_type y = 0;
	element_type width = 0;
	element_type height = 0;
};

using Rectanglei = Rectangle<int>;
using Rectanglef = Rectangle<float>;
using Rectangled = Rectangle<double>;

NGS_MATH_END