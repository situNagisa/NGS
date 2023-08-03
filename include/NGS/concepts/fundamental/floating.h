#pragma once

#include "NGS/concepts/constant.h"

NGS_CCPT_BEGIN

template<class T = void>
concept Float = Constant<T> && std::is_floating_point_v<typename T::value_type>;

NGS_CCPT_END
