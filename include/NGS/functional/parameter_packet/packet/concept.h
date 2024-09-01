#pragma once

#include "./defined.h"

NGS_LIB_MODULE_BEGIN

template<class T>
concept packet_like = statics::tuples::tuple<T>;

NGS_LIB_MODULE_END