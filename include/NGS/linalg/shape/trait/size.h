#pragma once

#include "./index.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

template<class T>
using size_t = ::std::make_unsigned_t<index_t<T>>;

NGS_LIB_MODULE_END