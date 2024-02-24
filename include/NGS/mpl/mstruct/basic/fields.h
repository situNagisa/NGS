#pragma once

#include "./defined.h"

NGS_LIB_MODULE_BEGIN

template<class> struct fields {};
template<class T>
using fields_t = typename fields<T>::type;

template<class T> requires requires{ typename type_traits::object_t<T>::fields_type; }
struct fields<T>{ using type = typename type_traits::object_t<T>::fields_type; };

NGS_LIB_MODULE_END