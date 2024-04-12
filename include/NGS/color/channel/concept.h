#pragma once

#include "./trait.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

template<class T>
concept color_channel = ::std::is_object_v<underlying_type_t<T>>;

template<class T>
concept arithmetic_channel = color_channel<T> && ::std::is_arithmetic_v<underlying_type_t<T>> && requires
{
	{ NGS_LIB_MODULE_NAME::bit_count<T>() } -> ::std::convertible_to<::std::size_t>;
} && ( bits::algorithm::bit_of<underlying_type_t<T>>() >= (NGS_LIB_MODULE_NAME::bit_count<T>()) );

NGS_LIB_MODULE_END