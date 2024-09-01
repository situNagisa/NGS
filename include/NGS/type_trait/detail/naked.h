#pragma once

#include "./defined.h"

NGS_LIB_MODULE_BEGIN

template<class Type>
using naked_t = ::std::remove_cvref_t<Type>;

NGS_LIB_MODULE_END
