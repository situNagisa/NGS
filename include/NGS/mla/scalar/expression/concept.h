#pragma once

#include "NGS/mla/base/expression.h"

NGS_MLA_BEGIN

template<class _Expression>
concept CScalarExpression = CArithmetic<_Expression>;

NGS_MLA_END
