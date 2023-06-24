#pragma  once

#include "NGS/base/STL.h"
#include "NGS/base/defined.h"

NGS_BEGIN


NGS_TYPE_TRAIT

/**
 * @brief create a 1 meta predicate
 *
 * function create_predicate1(bool meta_function(class,class...),class... classes):function(class)->bool{
 *		return new function(class cla)->bool{return meta_function(cla,classes...);};
 * }
 */
	template<template<class...>class _MetaFunc, class... _Args>
struct create_predicate1 {
	template<class _First>
	struct type {
		using type = _First;
		constexpr static bool value = _MetaFunc<_First, _Args...>::value;
	};
};

template<class _Input>
template<template<class...>class _MetaFunc, class... _Args>
using create_predicate1_t = typename create_predicate1<_MetaFunc, _Args...>::template type<_Input>;





NGS_END
NGS_END