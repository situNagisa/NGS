#pragma once

#include "NGS/math/mla/base/expression.h"

NGS_MLA_BEGIN

template<class _Expression>
concept CScalarExpression = CArithmetic<_Expression>;

NGS_MLA_END
