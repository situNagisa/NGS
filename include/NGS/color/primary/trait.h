#pragma once

#include "./defined.h"

NGS_LIB_MODULE_BEGIN

template<class _T>
struct traits;

template<class _T> requires
color_channel<typename type_traits::object_t<_T>::alpha_type>&&
color_channel<typename type_traits::object_t<_T>::red_type>&&
color_channel<typename type_traits::object_t<_T>::green_type>&&
color_channel<typename type_traits::object_t<_T>::blue_type>
struct traits<_T>
{
	using object_type = type_traits::object_t<_T>;
	using alpha_type = typename object_type::alpha_type;
	using red_type = typename object_type::red_type;
	using green_type = typename object_type::green_type;
	using blue_type = typename object_type::blue_type;
};

NGS_LIB_MODULE_END