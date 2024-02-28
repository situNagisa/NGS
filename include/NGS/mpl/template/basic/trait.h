#pragma once

#include "./defined.h"

NGS_LIB_MODULE_BEGIN

namespace _detail
{

	template<class>
	struct trait;
	template<template<class ...>class Template, class ...Args>
	struct trait < Template<Args...> > {
		using value_type = Template<Args...>;
		static constexpr size_t arg_count = sizeof... (Args);

		template<typename...NewArgs>
		using re_arg = Template<NewArgs...>;

		template<template<class ...>class  NewTemplate>
		using re_template = NewTemplate<Args...>;
	};

}

NGS_LIB_MODULE_END