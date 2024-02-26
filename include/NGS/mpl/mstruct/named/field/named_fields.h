#pragma once

#include "./concept.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

namespace _detail
{
	template<class>
	struct named_fields : ::std::false_type {};

	template<template<class...>class Template,class... Field>
	struct named_fields<Template<Field...>> : ::std::bool_constant<(named_field<Field> && ...)>{};
}

template<class T>
concept named_fields = _detail::named_fields<type_traits::naked_t<T>>::value;

NGS_LIB_MODULE_END