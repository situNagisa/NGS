#pragma once

#include "../channel.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

template<class>
struct primary_traits;

template<class T> requires requires
{
	typename type_traits::object_t<T>::value_type;
	typename type_traits::object_t<T>::alpha_type;
	typename type_traits::object_t<T>::red_type;
	typename type_traits::object_t<T>::green_type;
	typename type_traits::object_t<T>::blue_type;
}
struct primary_traits<T>
{
	using object_type = type_traits::object_t<T>;

	using value_type = typename object_type::value_type;
	using alpha_type = typename object_type::alpha_type;
	using red_type = typename object_type::red_type;
	using green_type = typename object_type::green_type;
	using blue_type = typename object_type::blue_type;
};

template<class T> requires requires { typename primary_traits<T>::value_type; }
using primary_value_t = typename primary_traits<T>::value_type;

template<class T> requires requires { typename primary_traits<T>::alpha_type; }
using primary_alpha_t = typename primary_traits<T>::alpha_type;
template<class T> requires requires { typename primary_traits<T>::red_type; }
using primary_red_t = typename primary_traits<T>::red_type;
template<class T> requires requires { typename primary_traits<T>::green_type; }
using primary_green_t = typename primary_traits<T>::green_type;
template<class T> requires requires { typename primary_traits<T>::blue_type; }
using primary_blue_t = typename primary_traits<T>::blue_type;

NGS_LIB_MODULE_END