#pragma once

#include "../size.h"
#include "./tuple.h"
#include "./defined.h"

NGS_LIB_BEGIN

template<class _Tuple > requires requires { {type_traits::object_t<_Tuple>::sequence_size} -> ::std::convertible_to<size_t>; }
struct size<_Tuple> : ccpt::constant_<size_t, type_traits::object_t<_Tuple>::sequence_size> {};

NGS_LIB_END
