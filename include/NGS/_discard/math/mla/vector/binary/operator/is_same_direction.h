#pragma once

#include "NGS/math/mla/vector/expression/concept.h"
#include "NGS/math/mla/vector/binary/operator/product.h"

NGS_MLA_BEGIN

template<CVectorExpression _Expression1,CVectorExpression _Expression2> requires CVectorSameDimension<_Expression1,_Expression2>
constexpr bool is_same_direction(const _Expression1& expression1,const _Expression2& expression2) noexcept
{
	return product_inner(expression1, expression2) > 0;
}

NGS_MLA_END
