#pragma once

#include "NGS/concepts/fundamental/constant.h"

NGS_CCPT_BEGIN

template<class T = void>
concept Int = Constant<T> && std::is_integral_v<typename T::value_type>;

template<long long _Value>
using int_ = constant<decltype(_Value), _Value>;

NGS_CCPT_END
