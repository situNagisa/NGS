#pragma once

#include "NGS/math/space/config.h"
#include "./defined.h"

NGS_SPACE_CARTESIAN_3D_BEGIN

enum class chirality {
	right,
	left,
#if NGS_SPACE_STANDARD_CHIRALITY == NGS_SPACE_CHIRALITY_RIGHT_HAND
	standard = right,
#elif NGS_SPACE_STANDARD_CHIRALITY == NGS_SPACE_CHIRALITY_LEFT_HAND
	standard = left,
#endif
};

NGS_SPACE_CARTESIAN_3D_END
