#pragma once

#include "NGS/math/space/defined.h"
#include "NGS/math/space/base/coordinate.h"
#include "NGS/math/space/orthographic/orthographic.h"
#include "NGS/math/space/orthographic/direction/concept.h"

NGS_COORDINATE_BEGIN

template<CAxis _Front, CAxis _Right, CAxis _Up>
struct direction : orthographic<_Front,_Right,_Up> {
	using front_type = _Front;
	using right_type = _Right;
	using up_type = _Up;
};

NGS_COORDINATE_END
