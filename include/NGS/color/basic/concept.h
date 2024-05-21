#pragma once

#include "../channel.h"
#include "./trait.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

namespace _detail
{
	template<template<class>class, class>
	struct channels_concept : ::std::false_type {};

	template<template<class>class Predicate, template<class...>class Template,class... Channel>
	struct channels_concept<Predicate, Template<Channel...>> : ::std::bool_constant<(Predicate<Channel>::value && ...)> {};

	NGS_CONCEPT_WRAPPER(color_channel, channels::color_channel);
	NGS_CONCEPT_WRAPPER(arithmetic_channel, channels::arithmetic_channel);
}

template <class T>
concept color = _detail::channels_concept<_detail::color_channel, type_traits::naked_t<color_channels_t<T>>>::value;

template<class T>
concept arithmetic_color = color<T> && _detail::channels_concept<_detail::arithmetic_channel, type_traits::naked_t<color_channels_t<T>>>::value;

NGS_LIB_MODULE_END
