#pragma once

#include "./constant_.h"

NGS_CCPT_BEGIN

template<class  T = void>
concept uint = constant<T> && std::is_unsigned_v<typename T::value_type>;

template<unsigned long long _Value>
using uint_ = constant_<decltype(_Value), _Value>;

NGS_CCPT_END
