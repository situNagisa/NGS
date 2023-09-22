#pragma once

#include "NGS/math/space/axis/axis.h"

NGS_COORDINATE_SUPPORT_BEGIN

struct  x : axis< 1, 0> {};
struct mx : axis<-1, 0> {};
struct  y : axis< 1, 1> {};
struct my : axis<-1, 1> {};
struct  z : axis< 1, 2> {};
struct mz : axis<-1, 2> {};
struct  w : axis< 1, 3> {};
struct mw : axis<-1, 3> {};

NGS_COORDINATE_SUPPORT_END
