#pragma once

#include "NGS/math/mst/set/expression/expression.h"


NGS_MST_BEGIN

template<class _Expression>
concept CInfiniteSetExpression = requires() {
	requires CSetExprerssion<_Expression>;
};

template<class _Expression>
struct InfiniteSetExpression : SetExpression<InfiniteSetExpression<_Expression>> {
	NGS_menvironment(InfiniteSetExpression);
public:
};

NGS_MST_END
