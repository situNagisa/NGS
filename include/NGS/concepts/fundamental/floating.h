#pragma once

#include "NGS/concepts/fundamental/constant.h"

NGS_CCPT_BEGIN

template<class T = void>
concept Float = Constant<T> && std::is_floating_point_v<typename T::value_type>;

template<double _Value>
using float_ = constant<double, _Value>;

NGS_CCPT_END
