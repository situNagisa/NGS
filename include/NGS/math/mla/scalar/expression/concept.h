#pragma once

#include "NGS/math/mla/base/expression.h"

NGS_MLA_BEGIN

template<class  _Expression>
concept CScalarExpression = std::is_arithmetic_v<_Expression>;

NGS_MLA_END
