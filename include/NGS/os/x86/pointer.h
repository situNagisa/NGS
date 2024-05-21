#pragma once

#include "./defined.h"

NGS_LIB_BEGIN

template<class T>
using pointer = pointers::pointer_32<T>;

using pointer_t = pointer<void>;

using pointer_underlying_t = ::std::uint32_t;

NGS_LIB_END