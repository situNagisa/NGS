#pragma once

#include "./scalar.h"

NGS_MATH_SCALAR_CONCEPTS_BEGIN

template<class _Left,class _Right>
concept can_plus_with = requires(_Left left, _Right right) { left + right; };

#define NGS_MATH_SCALAR_CONCEPTS_GEN_CONCEPT(name,op,)
//assign
//NGS_MATH_SCALAR_GEN_BINARY(assign, =);

//four operation
NGS_MATH_SCALAR_GEN_UNARY(auto_increase, ++);
NGS_MATH_SCALAR_GEN_UNARY(auto_decrease, --);
NGS_MATH_SCALAR_GEN_BINARY(plus, +);
NGS_MATH_SCALAR_GEN_BINARY(minus, -);
NGS_MATH_SCALAR_GEN_BINARY(muiltiply, *);
NGS_MATH_SCALAR_GEN_BINARY(divide, / );
//four operation assign
NGS_MATH_SCALAR_GEN_BINARY(plus_assign, +=);
NGS_MATH_SCALAR_GEN_BINARY(minus_assign, -=);
NGS_MATH_SCALAR_GEN_BINARY(muiltiply_assign, *=);
NGS_MATH_SCALAR_GEN_BINARY(divide_assign, /=);

//logic
NGS_MATH_SCALAR_GEN_UNARY(not_, !);
NGS_MATH_SCALAR_GEN_BINARY(and_, &&);
NGS_MATH_SCALAR_GEN_BINARY(or_, || );

//bit
NGS_MATH_SCALAR_GEN_UNARY(not_bit, ~);
NGS_MATH_SCALAR_GEN_BINARY(and_bit, &);
NGS_MATH_SCALAR_GEN_BINARY(or_bit, | );
//bit assign
NGS_MATH_SCALAR_GEN_BINARY(and_bit_assign, &=);
NGS_MATH_SCALAR_GEN_BINARY(or_bit_assign, |=);
//bit move
NGS_MATH_SCALAR_GEN_BINARY(right_move, >> );
NGS_MATH_SCALAR_GEN_BINARY(left_move, << );
//bit move assign
NGS_MATH_SCALAR_GEN_BINARY(right_move_assign, >>=);
NGS_MATH_SCALAR_GEN_BINARY(left_move_assign, <<=);

//sign
NGS_MATH_SCALAR_GEN_UNARY(positive, +);
NGS_MATH_SCALAR_GEN_UNARY(negative, -);

//compare
NGS_MATH_SCALAR_GEN_BINARY(greater, > );
NGS_MATH_SCALAR_GEN_BINARY(less, < );
NGS_MATH_SCALAR_GEN_BINARY(equal, == );
NGS_MATH_SCALAR_GEN_BINARY(greater_equal, >= );
NGS_MATH_SCALAR_GEN_BINARY(less_equal, <= );
NGS_MATH_SCALAR_GEN_BINARY(three_way, <=> );

//dereference
NGS_MATH_SCALAR_GEN_UNARY(deref, *);

NGS_MATH_SCALAR_CONCEPTS_END