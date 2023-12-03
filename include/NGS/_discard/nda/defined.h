#pragma once

#include "NGS/extend/extend.h"
#include "NGS/math/math.h"

#define NDA_BEGIN NGS_BEGIN namespace nda{
#define NDA_END } NGS_END

NDA_BEGIN

NGS_DEFINE_TYPE(number, float32);
NGS_DEFINE_TYPE(rect, Rectangle<number_t>);
NGS_DEFINE_TYPE(point, Point2<number_t>);

NGS_DEFINE_TYPE(matrix, mla::HomogeneousMatrix<3,number_t>);
inline constexpr auto identity_matrix = mla::identity_matrix_v<matrix_t::dimension, typename matrix_t::element_type>;

NGS_DEFINE_TYPE(color, StdARGB);

NDA_END
