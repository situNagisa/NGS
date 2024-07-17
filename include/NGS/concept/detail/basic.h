#pragma once

#include "./defined.h"

NGS_LIB_MODULE_BEGIN

template<class...>
concept none = false;

template<class...>
concept any = true;

template<class T>
concept fundamental = ::std::is_fundamental_v<T>;

template<class T>
concept function = ::std::is_function_v<T>;

template<class T>
concept enumeration = ::std::is_enum_v<T>;

template<class T>
concept scoped_enumeration = ::std::is_scoped_enum_v<T>;

template<class T>
concept object = ::std::is_object_v<T>;

template<class T>
concept pointer = ::std::is_pointer_v<T>;

NGS_LIB_MODULE_END