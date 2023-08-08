#pragma once

#include "NGS/mla/vector/expression/concept.h"
#include "NGS/mla/vector/unary/operator/length.h"
#include "NGS/mla/vector/binary/operator/basic.h"

NGS_MLA_BEGIN

template<CVectorExpression _Expression>
constexpr auto normalize(const _Expression& expr) { return divides_scalar(expr, length(expr)); }

NGS_MLA_END
