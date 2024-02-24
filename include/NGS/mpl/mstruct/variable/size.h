#pragma once

#include "./defined.h"

NGS_LIB_MODULE_BEGIN

template<class> struct variable_size {};
template<class Variable>
inline constexpr ::std::size_t variable_size_v = variable_size<Variable>::value;

template<class Variable> requires requires{ { type_traits::object_t<Variable>::size } -> ::std::convertible_to<::std::size_t>; }
struct variable_size<Variable> : ccpt::constant_<::std::size_t, type_traits::object_t<Variable>::size> {};

NGS_LIB_MODULE_END