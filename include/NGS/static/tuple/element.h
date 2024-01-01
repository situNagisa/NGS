#pragma once

#include "./defined.h"

NGS_LIB_BEGIN

template<size_t _Index, class _Tuple>
struct element;

template<size_t _Index, class _Tuple>
using element_t = typename element<_Index, _Tuple>::type;

NGS_LIB_END