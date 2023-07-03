#pragma once

#include "NGS/base/defined.h"
#include "NGS/base/boost/mpl.h"
#include "NGS/base/mpl/mpl_macro.h"

NGS_BEGIN

NGS_CONCEPT

template<typename T>
concept CPredicate = requires() {
	typename T::type;
	{ T::value } -> std::convertible_to<bool>;
};

NGS_END

NGS_MPL_BEGIN

/**
 * @brief 查找参数列表中第一个满足条件的类型
 *
 * @param condition 第二个参数的值
 * @param result_of_predicate 条件分支
 * @param result_of_rest_predicates... 参数
 *
 * @return 谓词的类型
 * @return 谓词的值
*/
NGS_mif(_FindIf, CPredicate _PredicateTrue, class... _Predicates) {
	NGS_mreturn_t typename _PredicateTrue::type;
	NGS_mreturn true;
};

NGS_mif_case(_FindIf, CPredicate _PredicateFalse) < false, _PredicateFalse > {
	NGS_mreturn false;
};
NGS_mif_case(_FindIf, CPredicate _PredicateFalse, CPredicate _Predicate, class... _Predicates) < false, _PredicateFalse, _Predicate, _Predicates... > {
	NGS_mcst_t found = _FindIf<_Predicate::value, _Predicate, _Predicates...>;

	NGS_mreturn_t typename found::type;
	NGS_mreturn found::value;
};

/**
 * @brief 查找参数列表中第一个满足条件的类型
 *
 * @param predicate 一元谓词
 * @param args... 类型参数列表（至少有一个参数）
 *
 * @return 若找到则为 `满足条件谓词的类型`，否则为`<error_type>`
 * @return 若找到则为 `true`，否则为`false`
 */
template<template<class>class _Predicate, class _First, class... _Args>
using find_if = _FindIf<_Predicate<_First>::value, _Predicate<_First>, _Predicate<_Args>...>;

template<template<class>class _Predicate, class _First, class... _Args>
using find_if_t = typename find_if<_Predicate, _First, _Args...>::type;
template<template<class>class _Predicate, class _First, class... _Args>
constexpr bool find_if_v = find_if<_Predicate, _First, _Args...>::value;

template<class _Equal, class _First, class... _Args>
constexpr bool is_any_of_v = _FindIf<std::is_same_v<_Equal, _First>, std::is_same<_Equal, _First>, std::is_same<_Equal, _Args>...>::value;


NGS_END
NGS_END
