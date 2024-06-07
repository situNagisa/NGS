#pragma once

#include "./defined.h"


NGS_LIB_MODULE_BEGIN


using dimension_t = ::std::size_t;

template<class T>
struct max_dimension_of : ccpt::constant_<dimension_t, 0> {};

template<class T>
inline constexpr dimension_t max_dimension_of_v = max_dimension_of<T>::value;

template<external::stl::ranges::algorithm::static_sized_range T>
struct max_dimension_of<T> : ccpt::constant_<dimension_t, max_dimension_of_v<::std::ranges::range_value_t<T>> +1> {};

NGS_LIB_MODULE_END