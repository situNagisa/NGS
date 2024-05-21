#pragma once

#include "NGS/math/space/defined.h"
#include "NGS/math/space/axis/support.h"
#include "./cartesian.h"
#include "./3d/chirality.h"
#include "./defined.h"

NGS_SPACE_CARTESIAN_BEGIN
inline namespace support {

using standard_coordinate = cartesian<x, y, z>;

}
NGS_SPACE_CARTESIAN_END
