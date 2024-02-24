#pragma once

#include "./defined.h"

NGS_LIB_MODULE_BEGIN

template<class> struct field_count {};
template<class T>
inline constexpr ::std::size_t field_count_v = field_count<T>::value;

template<class T> requires requires{ { type_traits::object_t<T>::field_count } -> ::std::convertible_to<::std::size_t>; }
struct field_count<T> : ccpt::constant_<::std::size_t, type_traits::object_t<T>::field_count> {};

NGS_LIB_MODULE_END