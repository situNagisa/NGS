#pragma once

#include "NGS/math/mla/vector/binary/macro_begin.h"

NGS_MLA_BEGIN

NGS_MLA_VECTOR_BINARY_OPERATOR(+, ScalarPlusFunctor, plus);
NGS_MLA_VECTOR_BINARY_OPERATOR(-, ScalarMinusFunctor, minus);
NGS_MLA_VECTOR_BINARY_OPERATOR(*, ScalarMultipliesFunctor, multiplies);
NGS_MLA_VECTOR_BINARY_OPERATOR(/ , ScalarDividesFunctor, divides);

NGS_MLA_END

#include "NGS/math/mla/vector/binary/macro_end.h"