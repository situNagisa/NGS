#pragma once

#include "NGS/math/space/defined.h"
#include "NGS/math/space/base/coordinate.h"
#include "NGS/math/space/orthographic/orthographic.h"
#include "NGS/math/space/orthographic/screen/concept.h"

NGS_COORDINATE_BEGIN

/**
 * \brief 
 * 
 * \tparam _Horizontal	→
 * \tparam _Vertical	⬇
 * \tparam _Depth		*
 */
template<CAxis _Horizontal, CAxis _Vertical, CAxis _Depth>
struct screen : orthographic<_Horizontal, _Vertical, _Depth> {
	using horizontal_type = _Horizontal;
	using vertical_type = _Vertical;
	using depth_type = _Depth;
};

NGS_COORDINATE_END
