#pragma once

#include "NGS/math/space/axis/axis.h"

NGS_SPACE_SUPPORT_BEGIN

struct  x : axis<0,  1> {};
struct mx : axis<0, -1> {};
struct  y : axis<1,  1> {};
struct my : axis<1, -1> {};
struct  z : axis<2,  1> {};
struct mz : axis<2, -1> {};
struct  w : axis<3,  1> {};
struct mw : axis<3, -1> {};

NGS_SPACE_SUPPORT_END
