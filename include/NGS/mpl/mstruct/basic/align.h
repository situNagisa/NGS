#pragma once

#include "./defined.h"

NGS_LIB_MODULE_BEGIN

template<class> struct struct_align {};
template<class T>
inline constexpr layout::align_t struct_align_v = struct_align<T>::value;

template<class T> requires requires{{ type_traits::object_t<T>::align } -> layout::align;}
struct struct_align<T> : ccpt::constant_<layout::align_t, type_traits::object_t<T>::align> {};

NGS_LIB_MODULE_END