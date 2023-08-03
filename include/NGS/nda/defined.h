#pragma once

#include "NGS/extend/extend.h"
#include "NGS/math/math.h"

#define NDA_BEGIN NGS_BEGIN namespace nda{
#define NDA_END } NGS_END

NDA_BEGIN

NGS_DEFINE_TYPE(number, float32);
NGS_DEFINE_TYPE(rect, Rectangle<number_t>);
NGS_DEFINE_TYPE(point, Point2_<number_t>);
NGS_DEFINE_TYPE(matrix, Matrix<number_t>);

NGS_DEFINE_TYPE(color, StdARGB);

NDA_END

namespace nda = ::ngs::nda;