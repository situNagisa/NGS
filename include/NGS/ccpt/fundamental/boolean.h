#pragma once

#include "./constant_.h"

NGS_CCPT_BEGIN

template<class  T = void>
concept boolean = constant<T> && std::convertible_to<typename T::value_type, bool>;

template<bool _Value>
using bool_ = constant_<decltype(_Value), _Value>;

NGS_CCPT_END
