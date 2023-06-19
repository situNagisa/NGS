#pragma  once

#include "NGS/base/base.h"
#include "NGS/math/vector.h"
#include "NGS/math/rectangle.h"
#include "NGS/math/util.h"

NGS_BEGIN

template<_CPT Arithmetic Number = float>
class Matrix {
public:
	NGS_TYPE_DEFINE(Matrix<Number>, this);
	NGS_TYPE_DEFINE(Number, num);
	NGS_TYPE_DEFINE(Vector2D<Number>, vector);
	NGS_TYPE_DEFINE(Rectangle<Number>, rect);

public:
	constexpr Matrix(
		__num a = 1,
		__num b = 0,
		__num c = 0,
		__num d = 1,
		__num tx = 0,
		__num ty = 0
	) :
		a(a),
		b(b),
		c(c),
		d(d),
		tx(tx),
		ty(ty)
	{}
	constexpr Matrix(__this_ref_cst other) = default;

	__this_ref operator=(__this_ref_cst) = default;

	__this operator-()const { return *this * -1; }

	__this_ref operator +=(__this_ref_cst other) {
		a += other.a;
		b += other.b;
		c += other.c;
		d += other.d;
		tx += other.tx;
		ty += other.ty;
	}
	__this operator+(__this_ref_cst other)const { __this copy = *this; return (copy += other); }
	__this_ref operator -=(__this_ref_cst other) { *this += -other; return *this; }
	__this operator-(__this_ref_cst other)const { __this copy = *this; return (copy -= other); }
	__this_ref operator *=(__num value) {
		a *= value;
		b *= value;
		c *= value;
		d *= value;
		tx *= value;
		ty *= value;
		return *this;
	}
	__this operator *(__num value)const { __this copy = *this; return (copy *= value); }
	friend __this operator *(__num value, __this_ref_cst self) { __this copy = self; return (copy *= value); }
	__this_ref operator /=(__num value) {
		value = 1 / value;
		*this *= value;
		return (*this);
	}
	__this operator /(__num value)const { __this copy = *this; return (copy /= value); }

	/**
	* @brief 返回将 Matrix 对象表示的几何转换应用于指定点所产生的结果。
	*
	* @note 如果other为自己会导致计算错误
	*/
	__this_ref operator <<=(__this_ref_cst other) {
		__this copy = *this;
		a = copy.a * other.a + copy.c * other.b/* + copy.tx * other.u*/;
		c = copy.a * other.c + copy.c * other.d/* + copy.tx * other.v*/;
		tx = copy.a * other.tx + copy.c * other.ty + copy.tx/* * other.w*/;

		b = copy.b * other.a + copy.d * other.b/* + copy.ty * other.u*/;
		d = copy.b * other.c + copy.d * other.d/* + copy.ty * other.v*/;
		ty = copy.b * other.tx + copy.d * other.ty + copy.ty/* * other.w*/;

		return *this;
	}
	__this operator<<(__this_ref_cst other)const {
		__this copy = *this;
		copy <<= other;
		return copy;
	}
	friend __vector_ref operator<<= (__vector_ref vector, __this_ref_cst self) {
		__vector copy = vector;
		vector.x = copy.x * self.a + copy.y * self.c;
		vector.y = copy.x * self.b + copy.y * self.d;
		vector.x += self.tx;
		vector.y += self.ty;
		return vector;
	}
	friend __vector operator<< (__vector_ref_cst vector, __this_ref_cst self) {
		__vector copy = vector;
		copy.x = vector.x * self.a + vector.y * self.c;
		copy.y = vector.x * self.b + vector.y * self.d;
		copy.x += self.tx;
		copy.y += self.ty;
		return copy;
	}
	friend __rect_ref operator<<= (__rect_ref rect, __this_ref_cst self) {
		rect = (rect << self);
		return rect;
	}
	friend __rect operator<< (__rect_ref_cst rect, __this_ref_cst self) {
		__vector left_top(rect.Left(), rect.Top());
		__vector right_bottom(rect.Right(), rect.Bottom());
		left_top <<= self;
		right_bottom <<= self;
		__num width = right_bottom.x - left_top.x;
		__num height = right_bottom.y - left_top.y;

		__rect r = { left_top.x, left_top.y, width, height };
		r.Normalize();
		//发生旋转
		if (width * height != rect.Area()) {
			__vector right_top(rect.Right(), rect.Top());
			__vector left_bottom(rect.Left(), rect.Bottom());
			right_top <<= self;
			left_bottom <<= self;
			__rect rota_rect = {
				static_cast<__rect::__num>(right_top.x),
				static_cast<__rect::__num>(right_top.y),
				static_cast<__rect::__num>(left_bottom.x - right_top.x),
				static_cast<__rect::__num>(left_bottom.y - right_top.y)
			};
			rota_rect.Normalize();
			return r | rota_rect;
		}
		return r;
	}

	/**
	* @brief    如果给定预转换坐标空间中的点，则此方法返回发生转换后该点的坐标。
	* @brief    与使用 transformPoint() 方法应用的标准转换不同，
	* @brief    deltaTransformPoint() 方法的转换不考虑转换参数 tx 和 ty。
	*/
	__vector DeltaTransformPoint(__vector_ref_cst point)const {
		__vector copy = point;
		copy.x = point.x * a + point.y * c;
		copy.y = point.x * b + point.y * d;
		return copy;
	}
	__vector TransformPoint(__vector_ref_cst point)const { return point << *this; }

	__num ScaleX()const { return sqrt(a * a + b * b); }
	__num ScaleY()const { return sqrt(c * c + d * d); }

	__this_ref Identity() {
		a = d = 1;
		b = c = 0;
		tx = ty = 0;
		return *this;
	}
	void Invert();

	__num Determinant()const {
		return Abs(a * d - b * c);
	}

	__this_ref Apply(__this_ref_cst other) {
		return *this <<= other;
	}

	__this_ref Rotate(float radian) {
		float sin = Sin(radian);
		float cos = Cos(radian);
		__this copy = *this;
		a = copy.a * cos - copy.b * sin;
		b = copy.a * sin + copy.b * cos;
		c = copy.c * cos - copy.d * sin;
		d = copy.c * sin + copy.d * cos;
		tx = copy.tx * cos - copy.ty * sin;
		ty = copy.tx * sin + copy.ty * cos;
		return *this;
	}

	__this_ref Scale(__num sx, __num sy) {
		a *= sx;
		b *= sy;
		c *= sx;
		d *= sy;
		tx *= sx;
		ty *= sy;
		return *this;
	}
	__this_ref Translate(__num dx, __num dy) {
		tx += dx;
		ty += dy;
		return *this;
	}
	__this_ref Translate(__vector_ref_cst delta) {
		tx += delta.x;
		ty += delta.y;
		return *this;
	}
	__this_ref Tilt(float skewx, float skewy) {
		__num
			a_ = a,
			b_ = b,
			c_ = c,
			d_ = d;
		float tanx = Tan(skewx), tany = Tan(skewy);

		a = a_ + c_ * tany;
		c = a_ * tanx + c_;
		b = b_ + d_ * tany;
		d = b_ * tanx + d_;

		return *this;
	}

	__this_ref Set(
		__num a,
		__num b,
		__num c,
		__num d,
		__num tx,
		__num ty
	) {
		this->a = a;
		this->b = b;
		this->c = c;
		this->d = d;
		this->tx = tx;
		this->ty = ty;
		return *this;
	}
	void Set(__this_ref_cst other) {
		a = other.a;
		b = other.b;
		c = other.c;
		d = other.d;
		tx = other.tx;
		ty = other.ty;
	}

	__this_ref CreateBox(
		__num scaleX,
		__num scaleY,
		__num angle,
		__num tx,
		__num ty
	) {
		Identity();
		Rotate(angle);
		Scale(scaleX, scaleY);
		Translate(tx, ty);
		return *this;
	}
	void CreateGradientBox(
		__num width,
		__num height,
		__num angle = 0,
		__num tx = 0,
		__num ty = 0
	);

private:

public:
	__num a = {};
	__num b = {};
	__num c = {};
	__num d = {};
	__num tx = {};
	__num ty = {};
public:
	inline constexpr static __num u = 0;
	inline constexpr static __num v = 0;
	inline constexpr static __num w = 1;

};


NGS_END