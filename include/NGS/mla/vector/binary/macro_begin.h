#include "NGS/mla/vector/binary/traits.h"
#include "NGS/mla/scalar/binary/operator.h"
#include "NGS/mla/vector/scalar_expression.h"
#include "NGS/mla/scalar/expression/concept.h"

#define NGS_MLA_VECTOR_BINARY_OPERATOR(op,functor,function_name)		\
template<CVectorExpression _Expression1, CVectorExpression _Expression2>\
	requires (_Expression1::dimension == _Expression2::dimension)		\
constexpr vector_binary_scalar_traits_t<_Expression1, _Expression2, functor> function_name(const _Expression1& expr1, const _Expression2& expr2) {\
	return vector_binary_scalar_traits_t<_Expression1, _Expression2, functor>(expr1, expr2);\
}																		\
template<CVectorExpression _Expression1, CVectorExpression _Expression2>\
	requires (_Expression1::dimension == _Expression2::dimension)		\
constexpr auto operator##op(const _Expression1& expr1, const _Expression2& expr2) {\
	return function_name(expr1, expr2);									\
}																		\
//

#define NGS_MLA_VECTOR_BINARY_SCALAR_OPERATOR(op,functor,function_name)	\
template<CVectorExpression _Expression, CScalarExpression _ElementType>	\
constexpr vector_binary_scalar_traits_t<_Expression, vector_scalar_expression_t<_Expression::dimension,_ElementType>, functor> function_name(const _Expression& expression, _ElementType scalar) {\
	using scalar_expr = vector_scalar_expression_t<_Expression::dimension,_ElementType>;\
	return vector_binary_scalar_traits_t<_Expression, scalar_expr, functor>(expression, scalar_expr(scalar));\
}																		\
template<CVectorExpression _Expression, CScalarExpression _ElementType>	\
constexpr vector_binary_scalar_traits_t<vector_scalar_expression_t<_Expression::dimension,_ElementType>, _Expression, functor> function_name(_ElementType scalar, const _Expression& expression) {\
	using scalar_expr = vector_scalar_expression_t<_Expression::dimension,_ElementType>;\
	return vector_binary_scalar_traits_t<scalar_expr, _Expression, functor>(scalar_expr(scalar), expression);\
}																		\
template<CVectorExpression _Expression, CScalarExpression _ElementType>	\
constexpr auto operator##op(const _Expression& expression, _ElementType scalar) {\
	return function_name(expression, scalar);							\
}																		\
template<CVectorExpression _Expression, CScalarExpression _ElementType>	\
constexpr auto operator##op(_ElementType scalar, const _Expression& expression) {\
	return function_name(scalar, expression);							\
}																		\
//

#define NGS_MLA_VECTOR_BINARY_ASSIGN_OPERATOR(op)						\
template<CVectorContainer _Container, CVectorExpression _Expression>	\
	requires (_Container::dimension == _Expression::dimension)			\
_Container& operator##op##=(_Container& container,const _Expression& expression) {	\
	return container.assign(container op expression);					\
}																		\
//
