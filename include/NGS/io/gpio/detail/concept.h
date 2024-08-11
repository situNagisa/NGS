#pragma once

#include "./trait.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

template<class T>
concept output_gpio = requires(T t, level level)
{
	{ set(NGS_PP_PERFECT_FORWARD(t), level) };
};

template<class T>
concept input_gpio = requires(T t)
{
	{ pin_level(NGS_PP_PERFECT_FORWARD(t)) } -> ::std::convertible_to<level>;
};

template<class T>
concept input_or_output_gpio = input_gpio<T> || output_gpio<T>;

template<class T>
concept input_and_output_gpio = input_gpio<T> && output_gpio<T>;

NGS_LIB_MODULE_END