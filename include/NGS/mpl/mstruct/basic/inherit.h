#pragma once

#include "./concept.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

namespace _detail
{
	template<template<class...>class Container,class...>
	struct cat
	{
		using type = Container<>;
	};

	template<template<class...>class Container, class First>
	struct cat<Container,First>
	{
		using type = Container<First>;
	};

	template<template<class...>class Container, template<class...>class FirstContainer,class... Firsts,template<class...>class SecondContainer,class... Seconds>
	struct cat<Container, FirstContainer<Firsts...>,SecondContainer<Seconds...>>
	{
		using type = Container<Firsts..., Seconds...>;
	};

	template<template<class...>class Container,class First,class Second, class... Rest>
	struct cat<Container,First,Second,Rest...>
	{
		using type = typename cat<Container, First, typename cat<Container, Second, Rest...>::type>::type;
	};

	template<template<auto,class...>class Struct, auto Align,class Fields>
	struct make_struct{};
	template<template<auto,class...>class Struct, auto Align, template<class...>class FieldContainer, class... Fields>
	struct make_struct<Struct,Align,FieldContainer<Fields...>>
	{
		using type = Struct<Align, Fields...>;
	};

	template<structure T, structure... Bases>
	struct inherit {};

	template<structure T>
	struct inherit<T> { using type = T; };

	template<template<auto,class...>class Struct,auto Align, class... Ts, structure... Bases>
	struct inherit<Struct<Align, Ts...>, Bases...>
	{
		using derived_type = Struct<Align, Ts... >;
		using type = typename make_struct<
			Struct,
			layout::align_of(struct_align_v< derived_type>, struct_align_v<Bases>...),
			typename cat<::boost::fusion::vector,fields_t<Bases>...,fields_t<derived_type>>::type
		>::type;
	};
}



NGS_LIB_MODULE_END