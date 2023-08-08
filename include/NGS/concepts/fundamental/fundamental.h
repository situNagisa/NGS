#pragma once

#include "NGS/concepts/defined.h"
#include "NGS/concepts/fundamental/floating.h"
#include "NGS/concepts/fundamental/int.h"
#include "NGS/concepts/fundamental/uint.h"

NGS_CCPT_BEGIN

template<class T>
concept Numeric = Int<T> || UInt<T> || Float<T>;

template<class T>
concept Fundamental = Numeric<T>;

NGS_CCPT_END
