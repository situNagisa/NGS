#pragma once

#include "NGS/base/base.h"


NGS_BEGIN

template<
	size_t N,
	_CPT Arithmetic Number,
	template<typename num>class Derived
>class _Vector {
private:
	using ___this = _Vector<N, Number, Derived>;
public:
	inline constexpr static auto DIMENSIONAL = N;
	using type = Number;

	template<_CPT Arithmetic C> using __similar = _Vector<N, C, Derived>;
	template<_CPT Arithmetic C> using __similar_ref = __similar<C>&;
	template<_CPT Arithmetic C> using __similar_ref_cst = const __similar<C>&;
	template<_CPT Arithmetic C> using __similar_ptr = __similar<C>*;
	template<_CPT Arithmetic C> using __similar_ptr_cst = const __similar<C>*;

	template<_CPT Arithmetic C> using __similar_d = Derived<C>;
	template<_CPT Arithmetic C> using __similar_d_ref = __similar<C>&;
	template<_CPT Arithmetic C> using __similar_d_ref_cst = const __similar<C>&;
	template<_CPT Arithmetic C> using __similar_d_ptr = __similar<C>*;
	template<_CPT Arithmetic C> using __similar_d_ptr_cst = const __similar<C>*;


	NGS_TYPE_DEFINE(___this, this);
	NGS_TYPE_DEFINE(Derived<Number>, derived);
	NGS_TYPE_DEFINE(Number, num);
	NGS_TYPE_DEFINE(size_t, size);

public:
	//=======================================
	//	构造函数
	//=======================================
	constexpr _Vector() = default;
	explicit(true) constexpr _Vector(__num x) :
		x(x)
	{}
	constexpr _Vector(__this_ref_cst) = default;
	template<_CPT Arithmetic C>
	constexpr _Vector(__similar_ref_cst<C> other) { _Construct(other); }

	//=======================================
	//	运算符重载
	//=======================================
	constexpr __num_ref    operator[](__size index) { return (&x)[index]; }
	constexpr  __num_ref_cst operator[](__size index)const { return (&x)[index]; }

	template<_CPT Arithmetic C>
	explicit(false) operator __similar_d<C>()const { return __similar_d<C>{*this}; }
	operator __derived_ref_cst()const { return static_cast<__derived_ref_cst>(*this); }
	operator __derived_ref() { return static_cast<__derived_ref>(*this); }

	auto         operator-()const { return (*this) * -1; }

	//auto         operator<=>(__this_ref_cst other)const;
	bool         operator==(__this_ref_cst other)const {
		for (__size i = 0; i < DIMENSIONAL; i++)
			if ((&x)[i] != other[i])return false;
		return true;
	}

	__this_ref operator=(__this_ref_cst other) {
		for (__size i = 0; i < DIMENSIONAL; i++)
			(&x)[i] = other[i];
		return *this;
	}
	//====================================
	// 加减法
	//====================================
	__derived_ref operator+=(__this_ref_cst other) {
		for (__size i = 0; i < DIMENSIONAL; i++)
			(&x)[i] += other[i];
		return *this;
	}
	__derived operator+(__this_ref_cst other)const {
		__derived clone(*this);
		clone += other;
		return clone;
	}
	__derived_ref operator-=(__this_ref_cst other) {
		for (__size i = 0; i < DIMENSIONAL; i++)
			(&x)[i] -= other[i];
		return *this;
	}
	__derived operator-(__this_ref_cst other)const {
		__derived clone(*this);
		clone -= other;
		return clone;
	}


	//====================================
	// 乘除法
	// 定义：
	// 1）乘法为向量的各个维度直接相乘，结果还是向量
	// 2）除法为向量的各个维度直接相除，结果还是向量
	//====================================
	__derived_ref   operator*=(__this_ref_cst other) {
		for (__size i = 0; i < DIMENSIONAL; i++)
			(&x)[i] *= other[i];
		return *this;
	}
	__derived    operator*(__this_ref_cst other)const { return __derived{ *this } *= other; }
	__derived_ref   operator/=(__this_ref_cst other) {
		for (__size i = 0; i < DIMENSIONAL; i++)
			(&x)[i] /= other[i];
		return *this;
	}
	__derived    operator/(__this_ref_cst other)const { return __derived{ *this } /= other; }

	__derived_ref   operator*=(__num value) {
		for (__size i = 0; i < DIMENSIONAL; i++)
			(&x)[i] *= value;
		return *this;
	}
	__derived    operator*(__num value)const { return __derived{ *this } *= value; }
	friend __derived operator*(__num value, __this_ref_cst self) { return self * value; }
	__derived_ref   operator/=(__num value) {
		for (__size i = 0; i < DIMENSIONAL; i++)
			(&x)[i] /= value;
		return *this;
	}
	__derived    operator/(__num value)const { return __derived{ *this } /= value; }
	//====================================
	// 数量积
	// 向量积
	// 混合积
	//====================================
	constexpr auto operator%(__this_ref_cst other)const { return Dot(*this, other); }

	friend constexpr __num Dot(__this_ref_cst a, __this_ref_cst b) {
		__num sum = 0;
		for (__size i = 0; i < __this::DIMENSIONAL; i++)
			sum += (a[i] * b[i]);
		return sum;
	}
	/*constexpr static __num Cross(__this_ref_cst a , __this_ref_cst b) {
		return ::sqrt(a.LengthSquared() * b.LengthSquared()) * ::sin()
		return __derived(
			a.y * b.z - a.z * b.y,
			a.z * b.x - a.x * b.z,
			a.x * b.y - a.y * b.x
		);
	}
	constexpr static __num Mixed(__this_ref_cst a, __this_ref_cst b, __this_ref_cst c) {

	}*/


	//=======================================
	//	公共接口
	//=======================================
	constexpr void
		Fill(__num value) {
		for (__size i = 0; i < DIMENSIONAL; i++)
			(&x)[i] = value;
	}

	constexpr void SetZero() { Fill(0); }

	template<typename ...Args>
		requires (sizeof...(Args) > 0) && (sizeof...(Args) <= N)
	constexpr void Set(Args ...args) { _Set(args...); }

	constexpr  auto LengthSquared()const {
		__num ls = {};
		for (__size i = 0; i < DIMENSIONAL; i++)
			ls += (&x)[i] * (&x)[i];
		return ls;
	}
	constexpr auto Length()const { return ngs::Sqrt(LengthSquared()); }
protected:
	//=======================================
	//	实现
	//=======================================
	template<typename ...Args>
		requires (sizeof...(Args) <= DIMENSIONAL)
	constexpr void _Construct(Args ...args) {
		__size i = 0;
		(((&x)[i] = args, i++), ...);
	}

	template<_CPT Arithmetic C>
	constexpr void _Construct(__similar_ref_cst<C> other) {
		for (__size i = 0; i < DIMENSIONAL; i++)
			(&x)[i] = static_cast<__num>(other[i]);
	}

	template<__size index = 0, typename... Args>
		requires (index < N) && (sizeof...(Args) < N)
	constexpr void _Set(__num Value, Args... args) {
		(&x)[index] = Value;
		if constexpr (index < N - 1 && (sizeof...(args) > 0))_Set<index + 1>(args...);
	}

public:
	__num x = {};
};


template<_CPT Arithmetic Number = float>
class Vector2D : public _Vector<2, Number, Vector2D> {
private:
	using __base = _Vector<2, Number, Vector2D>;
public:
	NGS_TYPE_DEFINE(Vector2D<Number>, this);
	NGS_TYPE_DEFINE(Number, num);

public:
	using __base::_Vector;
	constexpr Vector2D(__num x, __num y) :
		__base(x),
		y(y)
	{}

	friend constexpr __num Cross(__this_ref_cst a, __this_ref_cst b) { return a.x * b.y - a.y * b.x; }
	friend constexpr __this Cross(__this_ref_cst a, __num s) { return __this(s * a.y, -s * a.x); }
	friend constexpr __this Cross(__num s, __this_ref_cst a) { return __this(-s * a.y, s * a.x); }
	friend constexpr __this_ref CrossEq(__this_ref a, __num s) { a.Set(s * a.y, -s * a.x); return a; }
	friend constexpr __this_ref CrossEq(__num s, __this_ref a) { a.Set(-s * a.y, s * a.x); return a; }

	constexpr __num operator^(__this_ref_cst other)const { return Cross(*this, other); }
	constexpr __this operator^(__num s)const { return Cross(*this, s); }
	friend constexpr __this operator^(__num s, __this_ref_cst a) { return Cross(s, a); }
	constexpr __this_ref operator^=(__num s) { return CrossEq(*this, s); }

	float64 Tan()const { return this->y / this->x; }
	float64 Cot()const { return this->x / this->y; }
	float64 Sin()const { return this->y / this->Length(); }
	float64 Cos()const { return this->x / this->Length(); }

	float64 ArcTan()const { return ::atan2(this->y, this->x); }
	float64 ArcCot()const { return ::atan2(this->x, this->y); }
	float64 ArcSin()const { return ::asin(Sin()); }
	float64 ArcCos()const { return ::acos(Cos()); }

public:
	__num y = {};
};
template<_CPT Arithmetic Number>
using Point2_ = Vector2D<Number>;

using Point2i = Point2_<int>;
using Point2f = Point2_<float>;
using Point2lf = Point2_<double>;
using Point2s = Point2_<size_t>;

template<_CPT Arithmetic Number = float>
class Vector3D : public _Vector<3, Number, Vector3D> {
private:
	using __base = _Vector<3, Number, Vector3D>;
public:
	NGS_TYPE_DEFINE(Vector3D<Number>, this);
	NGS_TYPE_DEFINE(Number, num);

public:
	using __base::_Vector;
	constexpr Vector3D(__num x, __num y, __num z)
		:__base(x)
		, y(y)
		, z(z)
	{}

	friend constexpr __this Cross(__this_ref_cst a, __this_ref_cst b) {
		return __this(
			a.y * b.z - a.z * b.y,
			a.z * b.x - a.x * b.z,
			a.x * b.y - a.y * b.x
		);
	}
	friend constexpr __this_ref CrossEq(__this_ref a, __this_ref_cst b) { return a = Cross(a, b); }

	constexpr __this operator^(__this_ref_cst other)const { return Cross(*this, other); }
	constexpr __this_ref operator^=(__this_ref_cst other) { return CrossEq(*this, other); }
public:
	__num y = {};
	__num z = {};
};

template<_CPT Arithmetic Number>
using Point3_ = Vector3D<Number>;

using Point3i = Point3_<int>;
using Point3f = Point3_<float>;
using Point3lf = Point3_<double>;
using Point3s = Point3_<size_t>;

template<_CPT Arithmetic Number = float>
class Vector4D : public _Vector<4, Number, Vector4D> {
private:
	using __base = _Vector<4, Number, Vector4D>;
public:
	NGS_TYPE_DEFINE(Vector4D<Number>, this);
	NGS_TYPE_DEFINE(Number, num);

public:
	using __base::_Vector;
	constexpr Vector4D(__num x, __num y, __num z, __num w)
		:__base(x)
		, y(y)
		, z(z)
		, w(w)
	{}

public:
	__num y = {};
	__num z = {};
	__num w = {};
};

template<_CPT Arithmetic Number>
using Point4_ = Vector4D<Number>;

using Point4i = Point4_<int>;
using Point4f = Point4_<float>;
using Point4lf = Point4_<double>;
using Point4s = Point4_<size_t>;

NGS_END