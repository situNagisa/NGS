#pragma once

#include "./defined.h"

NGS_LIB_MODULE_BEGIN

template<class>
struct underlying_type{};

template<class T> requires ::std::is_fundamental_v<T>
struct underlying_type<T> { using type = T; };

template<class T> requires requires{ typename type_traits::object_t<T>::underlying_type; }
struct underlying_type<T> { using type = typename type_traits::object_t<T>::underlying_type; };

template<class T>
using underlying_type_t = typename underlying_type<T>::type;

NGS_LIB_MODULE_END
