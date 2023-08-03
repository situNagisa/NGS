#pragma once

#include "NGS/concepts/constant.h"

NGS_CCPT_BEGIN

template<class T = void>
concept Int = Constant<T> && std::is_integral_v<typename T::value_type>;

NGS_CCPT_END
