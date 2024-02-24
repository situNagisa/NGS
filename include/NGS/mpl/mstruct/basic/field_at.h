#pragma once

#include "./fields.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

template<class Struct, ::std::size_t> struct field_at;

template<class Struct, ::std::size_t Index>
using field_at_t = typename field_at<Struct, Index>::type;

namespace _detail
{
	template<class, ::std::size_t>
	struct field_at{};

	template<template<class...>class Template,class... Ts, ::std::size_t Index>
	struct field_at<Template<Ts...>, Index>
	{
		using type = typename ::boost::fusion::result_of::value_at_c<::boost::fusion::vector<Ts...>, Index>::type;
	};
}

template<class Struct, ::std::size_t Index> requires requires{ typename fields_t<Struct>; }
struct field_at<Struct,Index>
{
	using type = typename _detail::field_at<fields_t<Struct>,Index>::type;
};

NGS_LIB_MODULE_END