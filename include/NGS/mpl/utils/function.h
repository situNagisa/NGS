#pragma once

#include "NGS/mpl/defined.h"

NGS_MPL_BEGIN

template<class _Function>
concept CFunction = std::is_function_v<_Function>;

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
NGS_mfunction(function_trait, CFunction  _Function);

NGS_mfunction(function_trait, class  _ReturnType, class ... _Args) < _ReturnType(_Args...) > {
	NGS_mcst_t return_type = _ReturnType;
	template<template<class ...>class  _NewFunc>
	NGS_mcst_t rebind = _NewFunc<_Args...>;

	NGS_mcst_t function_type = _ReturnType(_Args...);
	NGS_mcst size_t parameters_count = sizeof...(_Args);
};

NGS_mfunction(function_trait, class  _ReturnType, class  _Class, class ... _Args) < _ReturnType(_Class::*)(_Args...) > {
	NGS_mcst_t return_type = _ReturnType;
	template<template<class ...>class  _NewFunc>
	NGS_mcst_t rebind = _NewFunc< _Args...>;

	NGS_mcst_t function_type = return_type(_Args...);
	NGS_mcst size_t parameters_count = sizeof...(_Args) + 1;
};

NGS_MPL_END
