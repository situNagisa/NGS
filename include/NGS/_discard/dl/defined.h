#pragma once

#include "NGS/math/math.h"
#include "NGS/ngl/NGL.h"

#define NGS_DL_BEGIN NGS_BEGIN namespace display_list{
#define NGS_DL_END } NGS_END

NGS_DL_BEGIN

using arithmetic_type = float32;
using rectangle_type = Rectangle<arithmetic_type>;
using circle_type = Circle<arithmetic_type>;
using point_type = Point2<arithmetic_type>;
using matrix_type = mla::HomogeneousMatrix<3, arithmetic_type>;
using color_type = StdARGB;

inline constexpr auto identity_matrix = mla::identity_matrix_v<matrix_type::dimension, typename matrix_type::element_type>;

NGS_DL_END

NGS_BEGIN

namespace ndl = display_list;

NGS_END
