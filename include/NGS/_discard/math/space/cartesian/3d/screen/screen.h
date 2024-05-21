#pragma once

#include "NGS/math/space/cartesian/3d/defined.h"
#include "NGS/math/space/cartesian/cartesian.h"

NGS_SPACE_CARTESIAN_3D_BEGIN

/**
 * \brief
 *
 * \tparam _Horizontal	→
 * \tparam _Vertical	⬇
 * \tparam _Depth		*
 */
template<CAxis _Horizontal, CAxis _Vertical, CAxis _Depth>
struct screen : cartesian<_Horizontal, _Vertical, _Depth> {
	using horizontal_type = _Horizontal;
	using vertical_type = _Vertical;
	using depth_type = _Depth;
};

NGS_SPACE_CARTESIAN_3D_END
