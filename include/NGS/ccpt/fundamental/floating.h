#pragma once

#include "./constant_.h"

NGS_CCPT_BEGIN

template<class  T = void>
concept floating = constant<T> && std::is_floating_point_v<typename T::value_type>;

template<double _Value>
using float_ = constant_<double, _Value>;

NGS_CCPT_END
