#pragma once

#include "./defined.h"

NGS_LIB_MODULE_BEGIN

template<class Type>
using object_t = ::std::remove_reference_t<Type>;

NGS_LIB_MODULE_END
