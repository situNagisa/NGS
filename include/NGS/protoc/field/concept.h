#pragma once

#include "./trait.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

template<class T, class R>
concept field = ::std::predicate<decltype(check), T, R>;

NGS_LIB_MODULE_END