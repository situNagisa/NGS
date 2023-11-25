#pragma once

#include "./defined.h"

NGS_COLOR_BEGIN

template<class _T>
struct primary_traits;

template<class _T> requires
CChannel<typename type_traits::object_t<_T>::alpha_type>&&
CChannel<typename type_traits::object_t<_T>::red_type>&&
CChannel<typename type_traits::object_t<_T>::green_type>&&
CChannel<typename type_traits::object_t<_T>::blue_type>
struct primary_traits<_T>
{
	using object_type = type_traits::object_t<_T>;
	using alpha_type = typename object_type::alpha_type;
	using red_type = typename object_type::red_type;
	using green_type = typename object_type::green_type;
	using blue_type = typename object_type::blue_type;
};

NGS_COLOR_END