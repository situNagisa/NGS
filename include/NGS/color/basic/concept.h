#pragma once

#include "../channel.h"
#include "./trait.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

namespace _detail
{
	template<class>
	struct channels_concept : ::std::false_type {};

	template<template<class...>class Template,class... Channel>
	struct channels_concept<Template<Channel...>> : ::std::bool_constant<(channels::arithmetic_channel<Channel> && ...)> {};
}

template <class T>
concept color = _detail::channels_concept<type_traits::naked_t<color_channels_t<T>>>::value;

NGS_LIB_MODULE_END
