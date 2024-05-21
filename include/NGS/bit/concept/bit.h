#pragma once

#include "./defined.h"

NGS_LIB_MODULE_BEGIN

template<class T>
concept bit = ::std::convertible_to<T, bool>;

NGS_LIB_MODULE_END