#pragma once

#include "NGS/math/space/defined.h"
#include "NGS/math/space/cartesian/3d/defined.h"
#include "./concept.h"

NGS_SPACE_CARTESIAN_3D_BEGIN

template<CAxis _Front, CAxis _Up, CAxis _Right>
struct direction : cartesian<_Front, _Up, _Right> {
	using front_type = _Front;
	using up_type = _Up;
	using right_type = _Right;
};


NGS_SPACE_CARTESIAN_3D_END
