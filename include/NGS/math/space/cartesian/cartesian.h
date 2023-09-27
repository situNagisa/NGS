#pragma once

#include "NGS/math/space/base/coordinate.h"
#include "./defined.h"

NGS_SPACE_CARTESIAN_BEGIN

template<CAxis... _Axes>
struct cartesian : coordinate<_Axes...> {};

NGS_SPACE_CARTESIAN_END
