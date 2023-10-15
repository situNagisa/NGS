#pragma once

#include "NGS/math/mla/scalar/binary/functor.h"
#include "NGS/math/mla/scalar/binary/macro_begin.h"

#if NGS_COMPILER == NGS_MSVC
#pragma warning(push)
#pragma warning(disable: 4244)
#endif

NGS_MLA_BEGIN

NGS_MLA_SCALAR_BINARY_FUNCTOR((x + y), ScalarPlusFunctor, ScalarBinaryFunctor);
NGS_MLA_SCALAR_BINARY_FUNCTOR((x - y), ScalarMinusFunctor, ScalarBinaryFunctor);
NGS_MLA_SCALAR_BINARY_FUNCTOR((x* y), ScalarMultipliesFunctor, ScalarBinaryFunctor);
NGS_MLA_SCALAR_BINARY_FUNCTOR((x / y), ScalarDividesFunctor, ScalarBinaryFunctor);

NGS_MLA_SCALAR_BINARY_FUNCTOR((x = y), ScalarAssignFunctor, ScalarBinaryAssignFunctor);
NGS_MLA_SCALAR_BINARY_FUNCTOR((x += y), ScalarPlusAssignFunctor, ScalarBinaryAssignFunctor);
NGS_MLA_SCALAR_BINARY_FUNCTOR((x -= y), ScalarMinusAssignFunctor, ScalarBinaryAssignFunctor);
NGS_MLA_SCALAR_BINARY_FUNCTOR((x *= y), ScalarMultipliesAssignFunctor, ScalarBinaryAssignFunctor);
NGS_MLA_SCALAR_BINARY_FUNCTOR((x /= y), ScalarDividesAssignFunctor, ScalarBinaryAssignFunctor);
//NGS_MLA_SCALAR_BINARY_FUNCTOR((std::swap(x, y)), ScalarSwapFunctor, ScalarBinaryAssignFunctor);

NGS_MLA_END

#if NGS_COMPILER == NGS_MSVC
#pragma warning(pop)
#endif

#include "NGS/math/mla/scalar/binary/macro_end.h"