#pragma once

#include "./defined.h"

NGS_LIB_MODULE_BEGIN

namespace _detail
{
	template<class> struct is_template : ::std::false_type {};
	template<template<class ...>class Template, class ... Args> struct is_template < Template<Args...> > : ::std::true_type {};
}

template<class T>
concept template_class = _detail::is_template<type_traits::naked_t<T>>::value;

NGS_LIB_MODULE_END