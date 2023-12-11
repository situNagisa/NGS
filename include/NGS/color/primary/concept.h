#pragma once

#include "./trait.h"
#include "../concept.h"

NGS_LIB_MODULE_BEGIN

template<class _T, class _O = type_traits::object_t<_T>>
concept primary_color = color<_T> &&
color_channel<typename traits<_T>::alpha_type> &&
color_channel<typename traits<_T>::red_type> &&
color_channel<typename traits<_T>::green_type> &&
color_channel<typename traits<_T>::blue_type> && requires(_T color)
{
	typename _O::type;
	{ color.alpha() } -> std::convertible_to<typename traits<_T>::alpha_type::type>;
	{ color.red() } -> std::convertible_to<typename traits<_T>::red_type::type>;
	{ color.green() } -> std::convertible_to<typename traits<_T>::green_type::type>;
	{ color.blue() } -> std::convertible_to<typename traits<_T>::blue_type::type>;
};

NGS_LIB_MODULE_END

NGS_LIB_MODULE_EXPORT(primary_color);