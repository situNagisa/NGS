﻿#pragma once

#include "./defined.h"

NGS_LIB_BEGIN

template<class _Tuple>
struct size : ccpt::constant_<size_t, 0> {};

template<class _Tuple>
inline constexpr size_t size_v = size<_Tuple>::value;

NGS_LIB_END