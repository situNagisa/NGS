#pragma once

#include "./concept.h"
#include "./trait.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

template<template_class T, class... NewArg>
struct re_arg
{
	using type = type_traits::add_cvref_like_t<T, typename _detail::trait<type_traits::naked_t<T>>::template re_arg<NewArg...>>;
};

template<template_class T, class... NewArg>
using re_arg_t = typename re_arg<T, NewArg...>::type;

NGS_LIB_MODULE_END