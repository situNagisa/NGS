#pragma once

#include "./trait.h"
#include "../concept.h"

NGS_LIB_MODULE_BEGIN

template<class T>
concept primary_color = color<T> &&
color_channel<typename traits<T>::alpha_type> &&
color_channel<typename traits<T>::red_type> &&
color_channel<typename traits<T>::green_type> &&
color_channel<typename traits<T>::blue_type> && requires(T color)
{
	typename type_traits::object_t<T>::type;
	{ color.alpha() } -> std::convertible_to<typename traits<T>::alpha_type::type>;
	{ color.red() } -> std::convertible_to<typename traits<T>::red_type::type>;
	{ color.green() } -> std::convertible_to<typename traits<T>::green_type::type>;
	{ color.blue() } -> std::convertible_to<typename traits<T>::blue_type::type>;
};

NGS_LIB_MODULE_END

NGS_LIB_MODULE_EXPORT(primary_color);