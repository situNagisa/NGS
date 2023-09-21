#pragma once

#include "NGS/math/mst/set/expression/expression.h"

NGS_MST_BEGIN

template<class _Expression>
concept CFiniteSetExpression = requires(_Expression expr, const _Expression expr_cst) {
	//{ expr_cst.element_count() } -> std::convertible_to<size_t>;
	requires std::ranges::sized_range<_Expression>;
	requires CSetExprerssion<_Expression>;
};

template<class _Expression>
struct FiniteSetExpression : SetExpression<FiniteSetExpression<_Expression>> {
	NGS_menvironment(FiniteSetExpression);
public:

};

NGS_MST_END
