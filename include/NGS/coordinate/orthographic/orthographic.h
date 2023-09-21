#pragma once

#include "NGS/coordinate/defined.h"
#include "NGS/coordinate/base/coordinate.h"
#include "NGS/coordinate/orthographic/concept.h"

NGS_COORDINATE_BEGIN

template<CAxis... _Axes>
struct orthographic : coordinate<_Axes...> {};

NGS_COORDINATE_END
