﻿#pragma once

#include "NGS/NGS_Defined.h"
#include "NGS/NGS_STL.h"
#include "NGS/NGS_Concepts.h"

/**
 * 还差最后一步，语法上已经没问题了，但在宏的传参上还有问题，msvc允许接收空参数，但是gcc不行
 */

NGS_BEGIN

template<
	size_t _N,
	_CPT Arithmetic _ElementType,
	class _Derived
>
class _Vector {

#define _VECTOR_COMMA ,
#define _VECTOR_NOTHING 
#define _VECTOR_OTHER_ELEMENT_SEQUENCE other.template At<_I>()
	//声明一个序列函数
#define _VECTOR_DECLRATE_INDEX_SEQUENCE_FUNCTION(functionName,paramType,returnType,modifier)	\
	template<size_t... _I>																		\
	constexpr returnType functionName(paramType other, std::index_sequence<_I...> )modifier		\
//
	//序列函数表达式
#define _VECTOR_INDEX_SEQUENCE_EXPRESS(operate,expr,operate2,returnType)				\
	return (returnType)(((_AsChild().template At<_I>()) operate (expr)) operate2 ...);	\
//
	//定义一个序列函数
#define _VECTOR_DEFINE_INDEX_SEQUENCE_FUNCTION(functionName,paramType,operate,expr,operate2,returnType,modifier)	\
	_VECTOR_DECLRATE_INDEX_SEQUENCE_FUNCTION(functionName, paramType, returnType,modifier) {						\
		_VECTOR_INDEX_SEQUENCE_EXPRESS(operate,expr,operate2,returnType)											\
	}																												\
//
	//定义一个序列操作符,返回值为序列函数的值
#define _VECTOR_OPERATOR(functionName,paramType,operate,expr,operate2,returnType,modifier)						\
private:																										\
	_VECTOR_DEFINE_INDEX_SEQUENCE_FUNCTION(functionName,paramType,operate,expr, operate2,returnType,modifier)	\
public:																											\
	returnType operator operate(paramType other)modifier {														\
		return functionName(other, index_sequence);																\
	}																											\
//
	//定义一个序列操作符,返回值为自己
#define _VECTOR_OPERATOR_AND_RETURN_SELF(functionName,paramType,operate,expr,operate2,modifier)			\
private:																								\
	_VECTOR_DEFINE_INDEX_SEQUENCE_FUNCTION(functionName,paramType,operate,expr, operate2,void,modifier)	\
public:																									\
	modifier __derived_ref operator operate(paramType other)modifier {									\
		functionName(other, index_sequence);															\
		return *this;																					\
	}																									\
//
	//定义一个序列操作符，参数为自身类型，返回值为序列函数结果
#define _VECTOR_OPERATOR_WITH_OTHER(functionName,operate,operate2,returnType,modifier)												\
	_VECTOR_OPERATOR(functionName, __derived_ref_cst, operate, _VECTOR_OTHER_ELEMENT_SEQUENCE, operate2, returnType, modifier)		\
//
	//定义一个序列操作符，参数为自身类型，返回值为自己
#define _VECTOR_OPERATOR_WITH_OTHER_AND_RETURN_SELF(functionName,operate,operate2,modifier)											\
	_VECTOR_OPERATOR_AND_RETURN_SELF(functionName, __derived_ref_cst, operate, _VECTOR_OTHER_ELEMENT_SEQUENCE, operate2, modifier)	\
//
	//定义算术序列操作符，包括算术符本身以及算术赋值符，赋值符返回值为自己
#define _VECTOR_ARITHMETIC_OPERATOR_WITH_OTHER(functionName,operate)							\
	_VECTOR_OPERATOR_WITH_OTHER_AND_RETURN_SELF(functionName, operate##=, _VECTOR_COMMA, _VECTOR_NOTHING)\
	constexpr __derived operator operate(__derived_ref_cst other)const{							\
		return __derived{ _AsChild() } operate## = other;										\
	}																							\
//
	//定义算数序列操作符，包括算术符本身以及算术赋值符，赋值符返回值为元素类型
#define _VECTOR_OPERATE_WITH_ELEMENT(functionName,operate)										\
	_VECTOR_OPERATOR_AND_RETURN_SELF(functionName, __ele,operate##=,other, _VECTOR_COMMA,_VECTOR_NOTHING)\
	constexpr __derived operator operate(__ele other)const {									\
		return __derived{ _AsChild() } operate## = other;										\
	}																							\
//

public:
	constexpr static size_t DIMENSIONAL = _N;
	using type = _ElementType;
private:

	NGS_TYPE_DEFINE(_ElementType, ele);
	NGS_TYPE_DEFINE(_Derived, derived);
	using ___this = _Vector<DIMENSIONAL, __ele, __derived>;
	NGS_TYPE_DEFINE(___this, this);

	using calcurateType = std::conditional_t < std::floating_point<__ele>, ngs::float64, std::conditional_t<std::signed_integral<__ele>, ngs::int64, ngs::uint64>>;
	static constexpr auto index_sequence = std::make_index_sequence<DIMENSIONAL>();
protected:
	_Vector() = default;
public:
	//向下转换
	operator __derived_ref() { return _AsChild(); }
	operator __derived_ref_cst()const { return _AsChild(); }

	constexpr __derived operator-()const { return *this * -1; }
	//bool operator==(__this_ref_cst other) const { return _Equal(other, index_sequence); }
	friend inline bool operator==(__derived_ref_cst a, __derived_ref_cst b) { return a._Equal(b, index_sequence); }
	_VECTOR_OPERATOR_AND_RETURN_SELF(_Copy, __derived_ref_cst, =, _VECTOR_OTHER_ELEMENT_SEQUENCE, _VECTOR_COMMA, _VECTOR_NOTHING);

	_VECTOR_ARITHMETIC_OPERATOR_WITH_OTHER(_Add, +);
	_VECTOR_ARITHMETIC_OPERATOR_WITH_OTHER(_Subtract, -);
	_VECTOR_ARITHMETIC_OPERATOR_WITH_OTHER(_Multpily, *);
	_VECTOR_ARITHMETIC_OPERATOR_WITH_OTHER(_Divide, / );

	_VECTOR_OPERATE_WITH_ELEMENT(_DivideNumber, / );
	_VECTOR_OPERATE_WITH_ELEMENT(_MultpilyNumber, *);
	friend inline __derived operator*(__ele element, __this_ref_cst self) { return self * element; }

	calcurateType operator%(__derived_ref_cst other) const { return _Dot(other, index_sequence); }

	constexpr auto LengthSquared()const { return *this % *this; }
	constexpr auto Length()const { return ngs::Sqrt(LengthSquared()); }

	void Fill(__ele value) { _Fill(value, index_sequence); }
	void SetZero() { Fill(0); }
	template<typename... T>
	void Set(T&&... args) { *this = __derived(std::forward<T>(args)...); }

	__ele_ref operator[](size_t index) { return *(&(_AsChild().template At<0>()) + index); }
	__ele_ref_cst operator[](size_t index) const { return *(&(_AsChild().template At<0>()) + index); }
public:
	constexpr __derived_ref _AsChild() { return *reinterpret_cast<__derived_ptr>(this); }
	constexpr __derived_ref_cst _AsChild()const { return *reinterpret_cast<__derived_ptr_cst>(this); }

	_VECTOR_DEFINE_INDEX_SEQUENCE_FUNCTION(_Equal, __derived_ref_cst, == , _VECTOR_OTHER_ELEMENT_SEQUENCE, &&, bool, const);
	_VECTOR_DEFINE_INDEX_SEQUENCE_FUNCTION(_Dot, __derived_ref_cst, *, _VECTOR_OTHER_ELEMENT_SEQUENCE, +, calcurateType, const);
	_VECTOR_DEFINE_INDEX_SEQUENCE_FUNCTION(_Fill, __ele, =, other, _VECTOR_COMMA, void, _VECTOR_NOTHING);

#undef _VECTOR_COMMA
#undef _VECTOR_NOTHING
#undef _VECTOR_OTHER_ELEMENT_SEQUENCE
#undef _VECTOR_INDEX_SEQUENCE_EXPRESS
#undef _VECTOR_DEFINE_INDEX_SEQUENCE_FUNCTION
#undef _VECTOR_OPERATOR
#undef _VECTOR_OPERATOR_AND_RETURN_SELF
#undef _VECTOR_OPERATOR_WITH_OTHER
#undef _VECTOR_OPERATOR_WITH_OTHER_AND_RETURN_SELF
#undef _VECTOR_OPERATE_WITH_ELEMENT
};

template<_CPT Arithmetic _ElementType>
class Vector2D : public _Vector<2, _ElementType, Vector2D<_ElementType>> {
private:
	using __base = _Vector<2, _ElementType, Vector2D<_ElementType>>;
	NGS_TYPE_DEFINE(_ElementType, ele);
	NGS_TYPE_DEFINE(Vector2D<_ElementType>, this);
public:
	constexpr Vector2D() = default;
	constexpr Vector2D(__ele x, __ele y)
		: x(x)
		, y(y)
	{}

	template<size_t _Pos>
	constexpr __ele_ref At() {
		if constexpr (_Pos == 0)
			return x;
		else if constexpr (_Pos == 1)
			return y;
		else
			throw std::out_of_range("访问的索引超出了向量的范围");
	}
	template<size_t _Pos>
	constexpr __ele_ref_cst At() const {
		if constexpr (_Pos == 0)
			return x;
		else if constexpr (_Pos == 1)
			return y;
		else
			throw std::out_of_range("访问的索引超出了向量的范围");
	}

	constexpr auto operator^(__this_ref_cst other) const {
		return x * other.y - y * other.x;
	}
	constexpr __this_ref_cst operator^=(__ele x) {
		__base::Set(x * y, -x * x);
		return *this;
	}
	constexpr __this operator^(__ele x) const {
		return __this{ *this } ^= x;
	}
	friend constexpr __this operator^(__ele x, __this_ref_cst self) {
		return { -x * self.y,x * self.x };
	}
	constexpr ngs::float64 Tan()const { return y / x; }
	constexpr ngs::float64 Cot()const { return x / y; }
	constexpr ngs::float64 Sin()const { return y / __base::Length(); }
	constexpr ngs::float64 Cos()const { return x / __base::Length(); }

	ngs::float64 ArcTan()const { return ::atan2(y, x); }
	ngs::float64 ArcCot()const { return ::atan2(x, y); }
	ngs::float64 ArcSin()const { return ::asin(Sin()); }
	ngs::float64 ArcCos()const { return ::acos(Cos()); }
public:
	__ele
		x, y;
};

template<_CPT Arithmetic Number>
using Point2_ = Vector2D<Number>;

using Point2i = Point2_<int>;
using Point2f = Point2_<float>;
using Point2lf = Point2_<double>;

template<_CPT Arithmetic _ElementType>
class Vector3D : public _Vector<3, _ElementType, Vector3D<_ElementType>> {
private:
	using __base = _Vector<3, _ElementType, Vector3D<_ElementType>>;
	NGS_TYPE_DEFINE(_ElementType, ele);
	NGS_TYPE_DEFINE(Vector3D<_ElementType>, this);
public:
	constexpr Vector3D() = default;
	constexpr Vector3D(__ele x, __ele y, __ele z)
		: x(x)
		, y(y)
		, z(z)
	{}
	template<size_t _Pos>
	constexpr __ele_ref At() {
		if constexpr (_Pos == 0)
			return x;
		else if constexpr (_Pos == 1)
			return y;
		else if constexpr (_Pos == 2)
			return z;
		else
			throw std::out_of_range("访问的索引超出了向量的范围");
	}
	template<size_t _Pos>
	constexpr __ele_ref_cst At() const {
		if constexpr (_Pos == 0)
			return x;
		else if constexpr (_Pos == 1)
			return y;
		else if constexpr (_Pos == 2)
			return z;
		else
			throw std::out_of_range("访问的索引超出了向量的范围");
	}

	__this_ref operator^=(__this_ref_cst other) {
		__base::Set(
			y * other.z - z * other.y,
			z * other.x - x * other.z,
			x * other.y - y * other.x
		);
		return *this;
	}
	constexpr __this operator^(__this_ref_cst other)const { return __this{ *this } ^= other; }

public:
	__ele
		x, y, z;
};

template<_CPT Arithmetic Number>
using Point3_ = Vector3D<Number>;

using Point3i = Point3_<int>;
using Point3f = Point3_<float>;
using Point3lf = Point3_<double>;


template<size_t _N, _CPT Arithmetic _ElementType>
class VectorND : public _Vector<_N, _ElementType, VectorND<_N, _ElementType>> {
private:
	using __base = _Vector<_N, _ElementType, Vector3D<_ElementType>>;
	NGS_TYPE_DEFINE(_ElementType, ele);
#define COMMA ,
	NGS_TYPE_DEFINE(VectorND<_N COMMA _ElementType>, this);
#undef COMMA
public:
	constexpr VectorND() = default;
	template<_CPT Arithmetic... Args>
	constexpr VectorND(Args... args)
		: data({ args... })
	{}
	template<size_t _Index>
	constexpr __ele_ref At() {
		return data[_Index];
	}
	template<size_t _Index>
	constexpr __ele_ref_cst At() const {
		return data[_Index];
	}
public:
	std::array<__ele, __base::DIMENSIONAL> data;
};

NGS_END
