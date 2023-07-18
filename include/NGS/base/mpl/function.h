#pragma once

#include "NGS/base/defined.h"
#include "NGS/base/boost/mpl.h"

NGS_BEGIN
NGS_MPL_BEGIN

/**
 * @brief 获取函数的`返回值类型`,`参数类型`, `参数个数`, `参数类型列表`
 *
 * @param function_type 函数类型
 *
 * @return 返回值类型
 * @return 参数类型
 * @return 参数个数
 * @return 参数类型列表
*/
NGS_mfunction(function_trait, class _Function);

NGS_mfunction(function_trait, class _ReturnType, class... _Args) < _ReturnType(_Args...) > {
	NGS_mcst_t return_type = _ReturnType;
	template<template<class...>class _NewFunc>
	NGS_mcst_t rebind = _NewFunc<_Args...>;

	NGS_mreturn_t _ReturnType(_Args...);
	NGS_mreturn sizeof...(_Args);
};

NGS_mfunction(function_trait, class _ReturnType, class _Class, class... _Args) < _ReturnType(_Class::*)(_Args...) > {
	NGS_mcst_t return_type = _ReturnType;
	template<template<class...>class _NewFunc>
	NGS_mcst_t rebind = _NewFunc< _Args...>;

	NGS_mreturn_t return_type(_Args...);
	NGS_mreturn sizeof...(_Args) + 1;
};

/**
 * @brief 获取函数的`返回值类型`,`参数类型`, `参数个数`, `参数类型列表`
 *
 * @param function_type 函数类型
 *
 * @return 函数类型
*/
template<class _Function>
using function_t = NGS_mget_return_t(function_trait<_Function>);
/**
 * @brief 获取函数的`返回值类型`,`参数类型`, `参数个数`, `参数类型列表`
 *
 * @param function_type 函数类型
 *
 * @return 返回值类型
*/
template<class _Function>
using function_return_t = NGS_mget_t(return_type, function_trait<_Function>);

template<class _Function>
constexpr size_t function_params_v = NGS_mget_return(function_trait<_Function>);

/**
 * @brief 包装函数，为元函数添加默认参数
 *
 * @param function 元函数
 * @param args... 默认参数列表
 *
 * @return 添加默认参数后的元函数
 */
NGS_mfunction(function_wrapper, template<class...>class _Function, class... _Args) {
	template<class... _Input>
	using meta_function = _Function<_Input..., _Args...>;
};

NGS_END
NGS_END
