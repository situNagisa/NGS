#pragma once

#include "./trait.h"
#include "./defined.h"

NGS_LIB_MODULE_BEGIN

template<class T, class Float = float>
concept pwm = ::std::invocable<decltype(set), T, Float>;

NGS_LIB_MODULE_END