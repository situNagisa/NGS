#pragma once

#include "NGS/math/defined.h"
#include "NGS/type_trait/type_trait.h"
#include "NGS/yap/yap.h"
#include "NGS/assert/assert.h"
#include "NGS/external/boost/stl_interfaces.h"
#include "NGS/wrapper/wrapper.h"
#include "NGS/functional/functional.h"
#include "NGS/math/basic.h"

#define NGS_MATH_LA_BEGIN NGS_MATH_BEGIN namespace linear_algebra {
#define NGS_MATH_LA_END } NGS_MATH_END

#define NGS_MATH_LA_SCALAR_BEGIN NGS_MATH_LA_BEGIN namespace scalars {
#define NGS_MATH_LA_SCALAR_END } NGS_MATH_LA_END

#define NGS_MATH_LA_VECTOR_BEGIN NGS_MATH_LA_BEGIN namespace vectors {
#define NGS_MATH_LA_VECTOR_END } NGS_MATH_LA_END

#define NGS_MATH_LA_MATRIX_BEGIN NGS_MATH_LA_BEGIN namespace matrices {
#define NGS_MATH_LA_MATRIX_END } NGS_MATH_LA_END

