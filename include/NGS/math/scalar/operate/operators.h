#pragma once

#include "./defined.h"
#include "./immediate.h"
#include "./expression.h"

NGS_MATH_SCALAR_BEGIN

#define NGS_MATH_SCALAR_GEN_OPERATOR(op,function,expression,...)	\
constexpr auto operator op(__VA_ARGS__)								\
	requires requires{ expression; }								\
{																	\
	return expression;												\
}																	\
//
#define NGS_MATH_SCALAR_GEN_UNARY(function, op)																			\
NGS_MATH_SCALAR_GEN_OPERATOR(op,function,function(NGS_PP_PERFECT_FORWARD(expression)),CScalarExpression auto&& expression)	\
//
#define NGS_MATH_SCALAR_GEN_BINARY(function,op)																															\
NGS_MATH_SCALAR_GEN_OPERATOR(op,function,function(NGS_PP_PERFECT_FORWARD(left),NGS_PP_PERFECT_FORWARD(right)),CScalarExpression auto&& left,CScalarExpression auto&& right)	\
//

//assign

//four operations
NGS_MATH_SCALAR_GEN_UNARY(auto_increase, ++);
NGS_MATH_SCALAR_GEN_UNARY(auto_decrease, --);
NGS_MATH_SCALAR_GEN_BINARY(plus, +);
NGS_MATH_SCALAR_GEN_BINARY(minus, -);
NGS_MATH_SCALAR_GEN_BINARY(multiply, *);
NGS_MATH_SCALAR_GEN_BINARY(divide, /);

NGS_MATH_SCALAR_GEN_BINARY(plus_assign, +=);
NGS_MATH_SCALAR_GEN_BINARY(minus_assign, -=);
NGS_MATH_SCALAR_GEN_BINARY(multiply_assign, *=);
NGS_MATH_SCALAR_GEN_BINARY(divide_assign, /=);

//logic
NGS_MATH_SCALAR_GEN_UNARY(not_, !);
NGS_MATH_SCALAR_GEN_BINARY(and_, &&);
NGS_MATH_SCALAR_GEN_BINARY(or_, || );

//bit
NGS_MATH_SCALAR_GEN_UNARY(not_bit, ~);
NGS_MATH_SCALAR_GEN_BINARY(and_bit, &);
NGS_MATH_SCALAR_GEN_BINARY(or_bit, | );
NGS_MATH_SCALAR_GEN_BINARY(and_bit_assign, &=);
NGS_MATH_SCALAR_GEN_BINARY(or_bit_assign, |=);
NGS_MATH_SCALAR_GEN_BINARY(right_move, >> );
NGS_MATH_SCALAR_GEN_BINARY(left_move, << );
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


#undef NGS_MATH_SCALAR_GEN_OPERATOR
#undef NGS_MATH_SCALAR_GEN_UNARY
#undef NGS_MATH_SCALAR_GEN_BINARY


NGS_MATH_SCALAR_END