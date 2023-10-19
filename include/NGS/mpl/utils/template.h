#pragma once

#include "NGS/mpl/defined.h"

NGS_MPL_BEGIN

/**
 * @brief 提取模板的参数列表
 *
 * @param template 模板
 *
 * @return `template`，模板的参数个数，模板替换，模板变换替换，模板应用，模板变换应用
*/
NGS_MPL_FUNCTION(template_trait, class);
NGS_MPL_FUNCTION(template_trait, template<class ...>class  _Template, class  ..._Args) < _Template<_Args...> > {
	NGS_MPL_TYPE template_type = _Template<_Args...>;
	NGS_MPL_VALUE size_t parameters_count = sizeof... (_Args);

	template<typename..._NewArgs>
	NGS_MPL_TYPE replace_parameters = _Template<_NewArgs...>;

	template<template<class ...>class  _NewTemplate>
	NGS_MPL_TYPE replace_template = _NewTemplate<_Args...>;
};

template<class  _Template, class ... _Args>
using replace_template_parameters_t = typename template_trait<_Template>::template replace_parameters<_Args...>;

template<class  _Template, template<class ...>class  _NewTemplate>
using replace_template_template_t = typename template_trait<_Template>::template replace_template<_NewTemplate>;

template<class, class >
constexpr bool is_same_template_v = false;
template<template<class ...>class  _Template, class ... _Args1, class ... _Args2>
constexpr bool is_same_template_v<_Template<_Args1...>, _Template<_Args2...>> = true;

template<class _Left, class _Right>
concept CSameTemplate = is_same_template_v<_Left, _Right>;

NGS_MPL_FUNCTION(is_template, class, template<class ...>class) : std::false_type{};
NGS_MPL_FUNCTION(is_template, template<class ...>class  _Template, class ... _Args) < _Template<_Args...>, _Template > : std::true_type{};

template<class  T, template<class ...>class  _Template>
constexpr bool is_template_v = is_template<T, _Template>::value;

template<class  T, template<class ...>class  _Template>
concept CTemplateFrom = is_template_v<T, _Template>;


NGS_MPL_END
