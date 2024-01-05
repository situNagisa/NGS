#pragma once

#include "NGS/math/mla/vector/expression/expression.h"
#include "NGS/math/mla/vector/unary/operator/polar_angle.h"
#include "NGS/math/mla/vector/binary/operator/product.h"
#include "NGS/math/mla/vector/unary/operator/modulus.h"

NGS_MLA_BEGIN

template<CVectorExpression _Left,CVectorExpression _Right>
constexpr auto angle_between(const _Left& left,const _Right& right){
	return std::acos(product_inner(left,right) / (modulus(left) * modulus(right)));
}

template<CVectorExpression _Begin, CVectorExpression _End>
constexpr auto angle_between_signed(const _Begin& begin, const _End& end) {
	auto b = polar_angle(begin);
	auto e = polar_angle(end);
	if(b < 0) b += 2 * std::numbers::pi;
	if(e < 0) e += 2 * std::numbers::pi;
	return e - b;
}

NGS_MLA_END
