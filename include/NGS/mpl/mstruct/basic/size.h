#pragma once

#include "./defined.h"

NGS_LIB_MODULE_BEGIN

template<class> struct struct_size {};
template<class T>
inline constexpr ::std::size_t struct_size_v = struct_size<T>::value;

template<class T> requires requires{ { type_traits::object_t<T>::size } -> ::std::convertible_to<::std::size_t>; }
struct struct_size<T> : ccpt::constant_<::std::size_t, type_traits::object_t<T>::size> {};

NGS_LIB_MODULE_END