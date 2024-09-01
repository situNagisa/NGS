#pragma once

#include "./defined.h"

NGS_LIB_MODULE_BEGIN

template<class>
struct pure_type_traits;

template<template<class...>class T, class... Args>
struct pure_type_traits<T<Args...>>
{
	template<template<class...>class T2>
	using replace_template = T2<Args...>;

	template<class... Args2>
	using replace_argument = T<Args2...>;

	using type = T<Args...>;
};

template<class T>
concept pure_type_template = requires { typename pure_type_traits<T>::type; };

template<pure_type_template T, template<class...>class NewTemplate>
using pure_type_rep_temp_t = typename pure_type_traits<T>::template replace_template<NewTemplate>;

template<pure_type_template T, class... NewArgs>
using pure_type_rep_arg_t = typename pure_type_traits<T>::template replace_argument<NewArgs...>;

NGS_LIB_MODULE_END