#include "NGS/mla/matrix/binary/binary.h"
#include "NGS/mla/scalar/binary.h"
#include "NGS/mla/matrix/container.h"
#include "NGS/mla/matrix/expression/scalar.h"

#define NGS_MLA_MATRIX_BINARY_OPERATOR(op,functor,function_name)		\
template<CMatrixExpression _Expression1, CMatrixExpression _Expression2>\
	requires is_similar<_Expression1, _Expression2>						\
constexpr matrix_binary_scalar_t<_Expression1, _Expression2, functor> function_name(const _Expression1& expr1, const _Expression2& expr2) {\
	return matrix_binary_scalar_t<_Expression1, _Expression2, functor>(expr1, expr2);\
}																		\
template<CMatrixExpression _Expression1, CMatrixExpression _Expression2>\
	requires is_similar<_Expression1, _Expression2>						\
constexpr auto operator##op(const _Expression1& expr1, const _Expression2& expr2) {\
	return function_name(expr1, expr2);									\
}																		\
template<CMatrixExpression _Expression, class _ElementType>				\
constexpr auto function_name##_scalar(const _Expression& expression, _ElementType scalar) {\
	using scalar_t = matrix_scalar_expression_t<matrix_traits<_Expression>::row_count, matrix_traits<_Expression>::col_count, _ElementType>;\
	using binary_t = matrix_binary_scalar_t<_Expression, scalar_t, functor>;\
	return binary_t(expression, scalar_t(scalar));						\
}																		\
template<CMatrixExpression _Expression, class _ElementType>				\
constexpr auto function_name##_scalar(_ElementType scalar, const _Expression& expression) {\
	using scalar_t = matrix_scalar_expression_t<matrix_traits<_Expression>::row_count, matrix_traits<_Expression>::col_count, _ElementType>;\
	using binary_t = matrix_binary_scalar_t<scalar_t, _Expression, functor>;\
	return binary_t(scalar_t(scalar), expression);						\
}																		\
template<CMatrixExpression _Expression, class _ElementType>				\
constexpr auto operator##op(const _Expression& expression, _ElementType scalar) { return function_name##_scalar(expression, scalar); }\
template<CMatrixExpression _Expression, class _ElementType>				\
constexpr auto operator##op(_ElementType scalar, const _Expression& expression) { return function_name##_scalar(scalar, expression); }\
template<CMatrixContainer _Container, CMatrixExpression _Expression> requires is_similar<_Container, _Expression>\
_Container& function_name##_assign(_Container& container, const _Expression& expression) { return container.assign(function_name(container, expression)); }\
template<CMatrixContainer _Container, class _ElementType>				\
_Container& function_name##_assign(_Container& container, _ElementType scalar) { return container.assign(function_name##_scalar(container, scalar)); }\
template<CMatrixContainer _Container, CMatrixExpression _Expression> requires is_similar<_Container, _Expression>\
_Container& operator##op##=(_Container& container, const _Expression& expression) { return function_name##_assign(container, expression); }\
template<CMatrixContainer _Container, class _ElementType>				\
_Container& operator##op##=(_Container& container, _ElementType scalar) { return function_name##_assign(container, scalar); }\
//
