#pragma once

#include "../variable.h"
#include "./field_count.h"
#include "./fields.h"
#include "./align.h"
#include "./size.h"
#include "./reflect.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

namespace  _detail
{
	template<class>
	struct valid_fields : ::std::false_type {};

	template<template<class...>class Template,variables::variable... Variables>
	struct valid_fields<Template<Variables...>> : ::std::true_type {};

	template<class T>
	inline constexpr bool valid_fields_v = valid_fields<T>::value;
}

template<class T>
concept structure = requires
{
	{ field_count<T>::value } -> ::std::convertible_to<::std::size_t>;
	requires _detail::valid_fields_v<fields_t<T>>;
	{ struct_size<T>::value } -> ::std::convertible_to<::std::size_t>;
	{ struct_align<T>::value } -> layout::align;
	requires reflectable<T>;
};

NGS_LIB_MODULE_END