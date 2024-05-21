#pragma once

#include "./defined.h"

NGS_LIB_MODULE_BEGIN

template<class T,class Under>
concept enum_under = cpt::enumeration<T> || ::std::convertible_to<T, Under>;

NGS_LIB_MODULE_END