#pragma once

#include "../defined.h"

NGS_BOOST_FUSION_RESULT_OF_BEGIN

template<template<class...>class Container, class...>
struct cat
{
	using type = Container<>;
};

template<template<class...>class Container, class First>
struct cat<Container, First>
{
	using type = Container<First>;
};

template<template<class...>class Container, template<class...>class FirstContainer, class... Firsts, template<class...>class SecondContainer, class... Seconds>
struct cat<Container, FirstContainer<Firsts...>, SecondContainer<Seconds...>>
{
	using type = Container<Firsts..., Seconds...>;
};

template<template<class...>class Container, class First, class Second, class... Rest>
struct cat<Container, First, Second, Rest...>
{
	using type = typename cat<Container, First, typename cat<Container, Second, Rest...>::type>::type;
};

template <template<class...>class Container, class... Rest>
using cat_t = typename cat<Container,Rest...>::type;

NGS_BOOST_FUSION_RESULT_OF_END

NGS_BOOST_FUSION_BEGIN



NGS_BOOST_FUSION_END
