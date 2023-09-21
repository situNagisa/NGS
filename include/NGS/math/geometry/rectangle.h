#pragma  once

#include "NGS/math/defined.h"
#include "NGS/math/util.h"
#include "NGS/math/geometry/point.h"

NGS_MATH_BEGIN

template<CArithmetic _ElementType>
struct NGS_API Rectangle {
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
	template<class  __ElementType>
	constexpr bool IsIntersect(const Rectangle<__ElementType>& other)const {
		using promote_type = mpl::promote_t<element_type, __ElementType>;
		return IsCross< promote_type>(Left(), Right(), other.Left(), other.Right()) && IsCross<promote_type>(Top(), Bottom(), other.Top(), other.Bottom());
	}

	template<class  __ElementType>
	constexpr auto Intersect(const Rectangle<__ElementType>& other)const {
		using result_type = mpl::promote_t<element_type, typename Rectangle<__ElementType>::element_type>;
		if (!IsIntersect(other))return Rectangle<result_type>{};
		return Rectangle<result_type>(
			std::max<result_type>(Left(), other.Left()),
			std::max<result_type>(Top(), other.Top()),
			std::min<result_type>(Right(), other.Right()),
			std::min<result_type>(Bottom(), other.Bottom())
		);
	}
	template<class  __ElementType>
	constexpr self_type& operator&=(const Rectangle<__ElementType>& other) { return (*this) = Intersect(other); }

	template<class  __ElementType>
	constexpr auto Union(const Rectangle<__ElementType>& other)const {
		using result_type = mpl::promote_t<element_type, typename Rectangle<__ElementType>::element_type>;
		return Rectangle<result_type>(
			std::min<result_type>(Left(), other.Left()),
			std::min<result_type>(Top(), other.Top()),
			std::max<result_type>(Right(), other.Right()),
			std::max<result_type>(Bottom(), other.Bottom())
		);
	}
	template<class  __ElementType>
	constexpr self_type& operator|=(const Rectangle<__ElementType>& other) { return (*this) = Union(other); }

	constexpr bool Contain(element_type x, element_type y)const { return In(x, Left(), Right()) && In(y, Top(), Bottom()); }
	constexpr bool Contain(const point_type& point)const { return Contain(point.x, point.y); }
	constexpr bool Contain(const self_type& other)const { return Contain(other.LeftTop()) && Contain(other.RightBottom()); }

	template<class  __ElementType>
	constexpr bool operator==(const Rectangle<__ElementType>& other)const { return x == other.x && y == other.y && width == other.width && height == other.height; }
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
	void Set(const point_type& position, const point_type& size) { Set(position.x, position.y, size.x, size.y); }
	void Set(element_type x, element_type y, const point_type& size) { Set(x, y, size.x, size.y); }
	void Set(const point_type& position, element_type width, element_type height) { Set(position.x, position.y, width, height); }

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

template<class  _ElementType1, class  _ElementType2>
constexpr bool is_intersect(const Rectangle<_ElementType1>& a, const Rectangle<_ElementType2>& b) { return a.IsIntersect(b); }
template<class  _ElementType1, class  _ElementType2>
constexpr auto intersect(const Rectangle<_ElementType1>& a, const Rectangle<_ElementType2>& b) { return a.Intersect(b); }
template<class  _ElementType1, class  _ElementType2>
constexpr auto operator&(const Rectangle<_ElementType1>& a, const Rectangle<_ElementType2>& b) { return intersect(a, b); }

template<class  _ElementType1, class  _ElementType2>
constexpr auto union_(const Rectangle<_ElementType1>& a, const Rectangle<_ElementType2>& b) { return a.Union(b); }
template<class  _ElementType1, class  _ElementType2>
constexpr auto operator|(const Rectangle<_ElementType1>& a, const Rectangle<_ElementType2>& b) { return union_(a, b); }

using Rectanglei = Rectangle<int>;
using Rectanglef = Rectangle<float>;
using Rectangled = Rectangle<double>;

NGS_MATH_END