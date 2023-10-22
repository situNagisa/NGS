#pragma once

#include "../defined.h"
#include "./floating.h"
#include "./integral.h"
#include "./uint.h"

NGS_CCPT_BEGIN

template<class  T>
concept number = integral<T> || uint<T> || floating<T>;

NGS_CCPT_END
