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
NGS_MPL_FUNCTION(template_trait, template<class ...>class  Template, class  ...Args) < Template<Args...> > {
	NGS_MPL_TYPE template_type = Template<Args...>;
	NGS_MPL_VALUE size_t parameters_count = sizeof... (Args);

	template<typename...NewArgs>
	NGS_MPL_TYPE replace_parameters = Template<NewArgs...>;

	template<template<class ...>class  NewTemplate>
	NGS_MPL_TYPE replace_template = NewTemplate<Args...>;
};

template<class  Template, class ... Args>
using replace_template_parameters_t = typename template_trait<Template>::template replace_parameters<Args...>;

template<class  Template, template<class ...>class  NewTemplate>
using replace_template_template_t = typename template_trait<Template>::template replace_template<NewTemplate>;

template<class, class >
constexpr bool is_same_template_v = false;
template<template<class ...>class  Template, class ... Args1, class ... Args2>
constexpr bool is_same_template_v<Template<Args1...>, Template<Args2...>> = true;

template<class Left, class Right>
concept CSameTemplate = is_same_template_v<Left, Right>;

NGS_MPL_FUNCTION(is_template, class, template<class ...>class) : std::false_type{};
NGS_MPL_FUNCTION(is_template, template<class ...>class  Template, class ... Args) < Template<Args...>, Template > : std::true_type{};

template<class  T, template<class ...>class  Template>
constexpr bool is_template_v = is_template<T, Template>::value;

template<class  T, template<class ...>class  Template>
concept CTemplateFrom = is_template_v<T, Template>;


NGS_MPL_END
