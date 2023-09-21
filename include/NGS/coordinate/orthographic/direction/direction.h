#pragma once

#include "NGS/coordinate/defined.h"
#include "NGS/coordinate/base/coordinate.h"
#include "NGS/coordinate/orthographic/orthographic.h"
#include "NGS/coordinate/orthographic/direction/concept.h"

NGS_COORDINATE_BEGIN

template<CAxis _Front, CAxis _Right, CAxis _Up>
struct direction : orthographic<_Front,_Right,_Up> {
	using front_type = _Front;
	using right_type = _Right;
	using up_type = _Up;
};

NGS_COORDINATE_END
