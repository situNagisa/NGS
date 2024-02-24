#pragma once

#include "./defined.h"

NGS_LIB_MODULE_BEGIN

template<class> struct variable_align {};
template<class Variable>
inline constexpr ::std::size_t variable_align_v = variable_align<Variable>::value;

template<class Variable> requires requires{ { type_traits::object_t<Variable>::align } -> ::std::convertible_to<::std::size_t>; }
struct variable_align<Variable> : ccpt::constant_<::std::size_t, type_traits::object_t<Variable>::align> {};

NGS_LIB_MODULE_END