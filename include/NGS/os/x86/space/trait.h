#pragma once

#include "../pointer.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

template<class>
struct underlying_type {};

template<class T> requires ::std::is_pointer_v<T>
struct underlying_type<T> { using type = pointer_t; };

template<class T> requires requires{ typename type_traits::object_t<T>::underlying_type; }
struct underlying_type<T> { using type = typename type_traits::object_t<T>::underlying_type; };

template<class T>
using underlying_type_t = typename underlying_type<T>::type;

NGS_LIB_MODULE_END