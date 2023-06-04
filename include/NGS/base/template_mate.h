#pragma once

#include "NGS/base/defined.h"
#include "NGS/base/STL.h"
#include "NGS/base/type_trait.h"
#include "NGS/base/concepts.h"

NGS_BEGIN

template<_CPT Arithmetic number1, _CPT Arithmetic number2>
using CompleteArithmetic = std::conditional_t<
	(sizeof(number1) >= sizeof(number2)),
	std::conditional_t <
	(sizeof(number1) != sizeof(number2)),
	number1,
	std::conditional_t <
	_CPT FloatingPoint<number1>,
	number1,
	std::conditional_t<
	_CPT UnsignedIntegral<number1>,
	number1,
	number2
	>
	>
	>
	, number2
>;


template<
	size_t start,
	size_t end,
	class Function,
	class...Args
>
	requires requires(Function f, size_t index, Args... args) {
	f(index, args...);
}
inline void For(Function fn, Args... args) {
	fn(start, args...);
	if constexpr (end - start >= 0 && start < end)
		For<start + 1, end>(fn, args...);
	else if constexpr (end - start < 0 && start >= end)
		For<start - 1, end>(fn, args...);
}
/*
NGS_EXPORT
template<
	_TYP SIZE_T16 start,
	_TYP SIZE_T16 end,
	class Lambda
>
NGS_INLINE _TYP VOID For(Lambda lambda) {
	lambda(start);
	if NGS_CONSTEXPR(end - start >= 0 && start < end)
		For<start + 1, end>(lambda);
	else if NGS_CONSTEXPR(end - start < 0 && start >= end)
		For<start - 1, end>(lambda);
}

//NGS_EXPORT
//template<
//    _TYP SIZE_T16 start,
//    _TYP SIZE_T16 end,
//    class ReturnType,
//    class Class,
//    _CPT Integral UINT
//>
//NGS_INLINE _TYP VOID For(ReturnType(Class::*fn)(UINT), Class* p) {
//    if NGS_CONSTEXPR(end - start >= 0) {
//        (p->*fn)(start);
//
//        if NGS_CONSTEXPR(start < end)
//            For<start + 1, end>(fn, p);
//    } else {
//        (p->*fn)(start);
//
//        if NGS_CONSTEXPR(start >= end)
//            For<start - 1, end>(fn, p);
//    }
//}

//15以下可在编译期计算，受限于constexpr
NGS_EXPORT
template<
	_TYP SIZE_T16 start,
	_TYP SIZE_T16 end,
	class ReturnType,
	_CPT Integral UINT
>
NGS_CONSTEXPR ReturnType For(ReturnType fn(UINT),ReturnType operate(ReturnType,ReturnType)) {
	ReturnType result = fn(start);
	if NGS_CONSTEXPR(end - start >= 0) {
		if NGS_CONSTEXPR(start < end)
			return operate(result, For<start + 1, end>(fn, operate));
		else
			return result;
	} else {
		if NGS_CONSTEXPR(start >= end)
			return operate(For<start - 1, end>(fn, operate), result);
		else
			return result;
	}
}

//15以下可在编译期计算，受限于constexpr
NGS_EXPORT
template<
	_TYP SIZE_T16 start,
	_TYP SIZE_T16 end,
	class Lambda,
	class ReturnType
>
NGS_CONSTEXPR ReturnType For(Lambda lambda, ReturnType operate(ReturnType, ReturnType)) {
	ReturnType result = lambda(start);
	if NGS_CONSTEXPR(end - start >= 0) {
		if NGS_CONSTEXPR(start < end)
			return operate(result, For<start + 1, end>(lambda, operate));
		else
			return result;
	} else {
		if NGS_CONSTEXPR(start >= end)
			return operate(For<start - 1, end>(lambda, operate), result);
		else
			return result;
	}
}

//15以下可在编译期计算，受限于constexpr
NGS_EXPORT
template<
	_TYP SIZE_T16 start,
	_TYP SIZE_T16 end,
	class Lambda,
	class Operate
>
NGS_CONSTEXPR auto For(Lambda lambda, Operate operate) {
	auto result = lambda(start);
	if NGS_CONSTEXPR(end - start >= 0) {
		if NGS_CONSTEXPR(start < end)
			return operate(result, For<start + 1, end>(lambda, operate));
		else
			return result;
	} else {
		if NGS_CONSTEXPR(start >= end)
			return operate(For<start - 1, end>(lambda, operate), result);
		else
			return result;
	}
}*/

//NGS_EXPORT
//template<
//    _TYP SIZE_T16 start,
//    _TYP SIZE_T16 end,
//    class ReturnType,
//    class Class,
//    _CPT Integral UINT
//>
//NGS_CONSTEXPR ReturnType For(ReturnType(Class::* fn)(UINT), Class* p, ReturnType operate(ReturnType, ReturnType)) {
//    if NGS_CONSTEXPR(end - start >= 0) {
//        ReturnType result = (p->*fn)(start);
//
//        if NGS_CONSTEXPR(start < end)
//            return operate(result, For<start + 1, end>(fn, p));
//        else
//            return result;
//    } else {
//        ReturnType result = (p->*fn)(start);
//
//        if NGS_CONSTEXPR(start >= end)
//            return operate(For<start - 1, end>(fn, p), result);
//        else
//            return result;
//    }
//}


NGS_END