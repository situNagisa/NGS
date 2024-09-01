#pragma once

#include "./defined.h"

NGS_LIB_MODULE_BEGIN

template<class>
struct pure_non_type_traits;

template<template<auto...>class T, auto... Args>
struct pure_non_type_traits<T<Args...>>
{
	template<template<auto...>class T2>
	using replace_template = T2<Args...>;

	template<auto... Args2>
	using replace_argument = T<Args2...>;

	using type = T<Args...>;
};

template<class T>
concept pure_non_type_template = requires { typename pure_non_type_traits<T>::type; };

template<pure_non_type_template T, template<auto...>class NewTemplate>
using pure_non_type_rep_temp_t = typename pure_non_type_traits<T>::template replace_template<NewTemplate>;

template<pure_non_type_template T, auto... NewArgs>
using pure_non_type_rep_arg_t = typename pure_non_type_traits<T>::template replace_argument<NewArgs...>;

NGS_LIB_MODULE_END