#pragma once

#include "./defined.h"

NGS_LIB_MODULE_BEGIN

template<class>
struct field_seq_trait : ::std::false_type {};

template<template<class...>class Template, class... Ts>
struct field_seq_trait<Template<Ts...>> : ::std::bool_constant<(fields::field<Ts> && ...)>
{
	using tuple_type = ::std::tuple<Ts...>;
	constexpr static auto size = sizeof...(Ts);
	constexpr static auto sizes = ::std::array{ static_cast<::std::size_t>(fields::size_v<Ts>)... };
	constexpr static auto aligns = ::std::array{ static_cast<::std::size_t>(fields::align_v<Ts>)... };
};

template<class T>
concept field_sequence = field_seq_trait<T>::value;

NGS_LIB_MODULE_END