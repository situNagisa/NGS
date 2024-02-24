#pragma once

#include "./defined.h"

NGS_LIB_MODULE_BEGIN

using variable_type_t = ::std::size_t;

template<variable_type_t Value>
using variable_reflect_constant = ccpt::constant_<variable_type_t, Value>;

template<class>
struct variable_type_reflect : variable_reflect_constant<0>{};

template<class T>
inline constexpr variable_type_t variable_type_reflect_v = variable_type_reflect<T>::value;

NGS_LIB_MODULE_END