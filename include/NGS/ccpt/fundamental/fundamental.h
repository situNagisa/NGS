#pragma once

#include "../defined.h"
#include "./floating.h"
#include "./int.h"
#include "./uint.h"

NGS_CCPT_BEGIN

template<class  T>
concept Numeric = Int<T> || UInt<T> || Float<T>;

template<class  T>
concept Fundamental = Numeric<T>;

NGS_CCPT_END
