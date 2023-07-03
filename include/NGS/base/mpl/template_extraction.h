#pragma once

#include "NGS/base/defined.h"
#include "NGS/base/boost/mpl.h"
#include "NGS/base/STL.h"

NGS_BEGIN
NGS_MPL_BEGIN

/**
 * @brief 提取模板的参数列表
 *
 * @param template 模板
 *
 * @return `template`，模板的参数个数，模板替换，模板变换替换，模板应用，模板变换应用
*/
NGS_mfunction(template_extract, class);


NGS_mfunction(template_extract, template<class...>class _Template, class ..._Args) < _Template<_Args...> > {
	NGS_mreturn_t _Template<_Args...>;
	NGS_mreturn sizeof... (_Args);

	template<typename..._NewArgs>
	NGS_mcst_t apply = _Template<_NewArgs...>;
	template<template<class>class _Transformer>
	NGS_mcst_t apply_transform = _Template<_Transformer<_Args>...>;

	template<class... _NewArgs>
	NGS_mcst_t template_type = _Template<_NewArgs...>;

	template<template<class...>class _NewTemplate>
	NGS_mcst_t replace = _NewTemplate<_Args...>;
	template<template<class...>class _NewTemplate, template<typename>class _Transformer>
	NGS_mcst_t replace_transform = _NewTemplate<_Transformer<_Args>...>;
};

template<class _Template, class... _Args>
using template_apply_t = typename template_extract<_Template>::template apply<_Args...>;
template<class _Template, template<class>class _Transformer>
using template_apply_transform_t = template_extract<_Template>::template apply_transform<_Transformer>;

template<class _Template, template<class...>class _NewTemplate>
using template_replace_t = typename template_extract<_Template>::template replace<_NewTemplate>;
template<class _Template, template<class...>class _NewTemplate, template<typename>class _Transformer>
using template_replace_transform_t = typename template_extract<_Template>::template replace_transform<_NewTemplate, _Transformer>;

template<class, class>
constexpr bool is_same_template_v = false;
template<template<class...>class A, class... _Args1, class... _Args2>
constexpr bool is_same_template_v<A<_Args1...>, A<_Args2...>> = true;

template<class, template<class...>class>
constexpr bool is_template_v = false;
template<template<class...>class _Template, class... _Args>
constexpr bool is_template_v<_Template<_Args...>, _Template> = true;


NGS_END
NGS_END
