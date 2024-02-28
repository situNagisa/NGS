#pragma once

#include "./concept.h"
#include "./trait.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

template<template_class T,template<class...>class NewTemplate>
struct re_template
{
	using type = type_traits::add_cvref_like_t<T, typename _detail::trait<type_traits::naked_t<T>>::template re_template<NewTemplate>>;
};

template<template_class T, template<class...>class NewTemplate>
using re_template_t = typename re_template<T,NewTemplate>::type;

NGS_LIB_MODULE_END