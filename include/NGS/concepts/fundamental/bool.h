#pragma once

#include "NGS/concepts/fundamental/constant.h"

NGS_CCPT_BEGIN

template<class  T = void>
concept Bool = Constant<T> && std::convertible_to<typename T::value_type, bool>;

template<bool _Value>
using bool_ = constant<decltype(_Value), _Value>;

NGS_CCPT_END
