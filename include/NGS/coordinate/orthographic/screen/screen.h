#pragma once

#include "NGS/coordinate/defined.h"
#include "NGS/coordinate/base/coordinate.h"
#include "NGS/coordinate/orthographic/orthographic.h"
#include "NGS/coordinate/orthographic/screen/concept.h"

NGS_COORDINATE_BEGIN

template<CAxis _Horizontal, CAxis _Vertical, CAxis _Depth>
struct screen : orthographic<_Horizontal, _Vertical, _Depth> {
	using horizontal_type = _Horizontal;
	using vertical_type = _Vertical;
	using depth_type = _Depth;
};

NGS_COORDINATE_END
