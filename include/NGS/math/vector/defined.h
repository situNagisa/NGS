#pragma once

#include "../defined.h"
#include "NGS/yap/yap.h"
#include "NGS/type_trait/type_trait.h"
#include "NGS/cpt/cpt.h"
#include "NGS/math/space.h"
#include "NGS/boost/stl_interfaces.h"

#define NGS_MATH_VECTOR_BEGIN NGS_MATH_BEGIN namespace vectors{
#define NGS_MATH_VECTOR_END } NGS_MATH_END

#define NGS_MATH_VECTOR_FUNCTOR_BEGIN NGS_MATH_VECTOR_BEGIN namespace functor{
#define NGS_MATH_VECTOR_FUNCTOR_END } NGS_MATH_VECTOR_END