#pragma once

#include "../defined.h"
#include "NGS/math/vector.h"

//for `NGS_ASSERT`
#include "NGS/base/base.h"

#define NGS_MATH_MATRIX_BEGIN NGS_MATH_BEGIN namespace matrixes{
#define NGS_MATH_MATRIX_END } NGS_MATH_END

#define NGS_MATH_MATRIX_FUNCTOR_BEGIN NGS_MATH_MATRIX_BEGIN namespace functor{
#define NGS_MATH_MATRIX_FUNCTOR_END } NGS_MATH_MATRIX_END