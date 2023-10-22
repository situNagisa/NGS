#pragma once

#include "./constant_.h"

NGS_CCPT_BEGIN

template<class  T = void>
concept integral = constant<T> && std::is_integral_v<typename T::value_type>;

template<long long _Value>
using int_ = constant_<decltype(_Value), _Value>;

NGS_CCPT_END
