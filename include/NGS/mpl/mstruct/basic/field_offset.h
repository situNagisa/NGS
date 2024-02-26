#pragma once

#include "../variable.h"
#include "./fields.h"
#include "./concept.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

namespace _detail
{
	template<class Fields, layout::align_t Align, ::std::size_t Index>
	struct field_offset_impl{};

	template<template<class...>class Container,class... Field,layout::align auto Align, ::std::size_t Index>
	struct field_offset_impl<Container<Field...>, Align, Index>
	{
		static constexpr ::std::size_t value = layout::offset<Align.align()>(variables::variable_size_v<Field>...)[Index];
	};
}

template<structure Struct, ::std::size_t Index>
struct field_offset
{
	static constexpr ::std::size_t value = _detail::field_offset_impl<fields_t<Struct>, variables::variable_align_v<Struct>, Index>::value;
};

template<structure Struct, ::std::size_t Index>
inline constexpr ::std::size_t field_offset_v = field_offset<Struct, Index>::value;

NGS_LIB_MODULE_END