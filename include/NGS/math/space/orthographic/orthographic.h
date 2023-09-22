#pragma once

#include "NGS/math/space/defined.h"
#include "NGS/math/space/base/coordinate.h"
#include "NGS/math/space/orthographic/concept.h"

NGS_COORDINATE_BEGIN

template<CAxis... _Axes>
struct orthographic : coordinate<_Axes...> {};

NGS_COORDINATE_END
