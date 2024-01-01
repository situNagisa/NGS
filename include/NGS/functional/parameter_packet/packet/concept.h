#pragma once

#include "./defined.h"

NGS_LIB_MODULE_BEGIN

template<class _T>
concept packet_like = statics::tuples::tuple_like<_T>;

NGS_LIB_MODULE_END